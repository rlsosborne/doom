#include <platform.h>
#include <stdlib.h>
#include "lcd.h"
#include "doom_display.h"

lcd_ports ports = {
  XS1_PORT_1G, /* clk */
  XS1_PORT_1F, /* de */
  XS1_PORT_16A, /* data */
  XS1_PORT_1B, /* hsync */
  XS1_PORT_1C, /* vsync */
  XS1_CLKBLK_1
};

extern "C" {
int doom_main(int argc, char **argv);
}

static void doom_task(int argc, char * unsafe * unsafe argv,
               client interface doom_display display)
{
  client interface doom_display * movable p = &display;
  doom_display_set_pointer(move(p));
  int status = doom_main(argc, argv);
  exit(status);
}

int main(int argc, char * unsafe * unsafe argv)
{
  interface uint_ptr_tx_slave to_buffer;
  interface uint_ptr_rx to_lcd;
  interface uint_ptr_tx from_lcd;
  interface uint_ptr_rx from_buffer;
  interface doom_display display;
  par {
    doom_task(argc, argv, display);
    uint_ptr_buffer_tx_slave(to_buffer, to_lcd);
    lcd_server(to_lcd, from_lcd, ports);
    uint_ptr_buffer(from_lcd, from_buffer);
    doom_display(display, to_buffer, from_buffer);
  }
  return 0;
}
