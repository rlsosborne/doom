#ifndef _lcd_h_
#define _lcd_h_

#include <xs1.h>
#include "lcd_defines.h"
#include "ptr_buffers.h"
/**
 * The structure to represent LCD port configuration
 */
typedef struct lcd_ports {
  out port lcd_clk; /**< The clock line */
  out port lcd_data_enabled; /**< The LCD data enabled */
#if LCD_STARTKIT_PORTS
  out buffered port:8 lcd_rgb_0_7;
  out buffered port:8 lcd_rgb_8_11;
  out buffered port:4 lcd_rgb_12_15;
#else
  out buffered port:16 lcd_rgb;
#endif
#if LCD_HOR_PULSE_WIDTH
  out buffered port:32 lcd_hsync; /**< The hsync line */
#endif
#if LCD_VERT_PULSE_WIDTH
  out buffered port:32 lcd_vsync; /**< The vsync line */
#endif
  clock clk_lcd; /**< Clock block used for LCD clock */
} lcd_ports;

/** \brief The LCD server thread.
 *
 * \param client The channel end connecting to the client.
 * \param ports The structure carrying the LCD port details.
 */
void lcd_server(client interface uint_ptr_rx rx,
                client interface uint_ptr_tx tx,
                lcd_ports &ports);

/** \brief LCD init function. This sets the lcd into a state where it is ready to accept data.
 *
 * \param c_lcd The channel end connecting to the lcd server.
 */
void lcd_init(chanend c_lcd);

#endif
