#include "lcd.h"
#include <xs1.h>

static void
output_row(struct lcd_ports &p, unsigned short row[LCD_ROW_WORDS * 2],
           unsigned &time)
{
  p.lcd_data_enabled @ time <: 1;
  unsigned data = row[0];
#if LCD_STARTKIT_PORTS
  p.lcd_rgb_0_7 @ time <: >> data;
  p.lcd_rgb_8_11 @ time <: data;
  p.lcd_rgb_12_15 @ time <: data >> 4;
#else
  p.lcd_rgb @ time <: data;
#endif

  time += LCD_WIDTH;

  p.lcd_data_enabled @ time <: 0;

  for (unsigned i = 1; i < LCD_ROW_WORDS * 2; i++) {
    unsigned data = row[i];
#if LCD_STARTKIT_PORTS
    p.lcd_rgb_0_7 <: >> data;
    p.lcd_rgb_8_11 <: data;
    p.lcd_rgb_12_15 <: data >> 4;
#else
    p.lcd_rgb <: data;
#endif
  }
}

void lcd_server(client interface uint_ptr_rx rx,
                client interface uint_ptr_tx tx,
                struct lcd_ports &p) {
  configure_clock_rate_at_least(p.clk_lcd, LCD_FREQ_DIVIDEND, LCD_FREQ_DIVISOR);
  configure_port_clock_output(p.lcd_clk, p.clk_lcd);
  set_port_inv(p.lcd_clk);
#if LCD_STARTKIT_PORTS
  configure_out_port(p.lcd_rgb_0_7, p.clk_lcd, 0);
  configure_out_port(p.lcd_rgb_8_11, p.clk_lcd, 0);
  configure_out_port(p.lcd_rgb_12_15, p.clk_lcd, 0);
#else
  configure_out_port(p.lcd_rgb, p.clk_lcd, 0);
#endif
  configure_out_port(p.lcd_data_enabled, p.clk_lcd, 0);

#if LCD_HOR_PULSE_WIDTH
  configure_out_port(p.lcd_hsync, p.clk_lcd, 1);
#endif

#if LCD_VERT_PULSE_WIDTH
  configure_out_port(p.lcd_vsync, p.clk_lcd, 1);
#endif

  start_clock(p.clk_lcd);

  unsigned * movable ptr = rx.pop();

  unsigned time = 100;

  while (1) {
#if (LCD_VERT_PULSE_WIDTH > 0)
    partout_timed(p.lcd_vsync, 1, 0, time);
#endif
    for (unsigned i = 0; i < LCD_VERT_PULSE_WIDTH; i++) {
#if (LCD_HOR_PULSE_WIDTH > 0)
      partout_timed(p.lcd_hsync, LCD_HOR_PULSE_WIDTH + 1,
                    1 << LCD_HOR_PULSE_WIDTH, time);
#endif
      time += LCD_HSYNC_TIME;
    }
#if (LCD_VERT_PULSE_WIDTH > 0)
    partout_timed(p.lcd_vsync, 1, 1, time);
#endif
#if (LCD_HOR_PULSE_WIDTH)
    for (unsigned i = 0;i < LCD_VERT_BACK_PORCH - LCD_VERT_PULSE_WIDTH; i++) {
      if (LCD_HOR_PULSE_WIDTH > 0)
        partout_timed(p.lcd_hsync, LCD_HOR_PULSE_WIDTH + 1,
                      1 << LCD_HOR_PULSE_WIDTH, time);
      time += LCD_HSYNC_TIME;
    }
#else
    time += LCD_HSYNC_TIME * (LCD_VERT_BACK_PORCH - LCD_VERT_PULSE_WIDTH);
#endif

    for (int y = 0; y < LCD_HEIGHT; y++) {
#if (LCD_HOR_PULSE_WIDTH > 0)
      partout_timed(p.lcd_hsync, LCD_HOR_PULSE_WIDTH + 1,
                    1 << LCD_HOR_PULSE_WIDTH, time);
#endif
      time += LCD_HOR_BACK_PORCH;

      if (!ptr)
        ptr = rx.pop();
      output_row(p, (unsigned short * movable)ptr, time);
      tx.push(move(ptr));
      time += LCD_HOR_FRONT_PORCH;
    }

    for (unsigned i = 0; i < LCD_VERT_FRONT_PORCH; i++) {
#if (LCD_HOR_PULSE_WIDTH > 0)
      partout_timed(p.lcd_hsync, LCD_HOR_PULSE_WIDTH + 1,
                    1 << LCD_HOR_PULSE_WIDTH, time);
#endif
      time += LCD_HSYNC_TIME;
    }
  }
}
