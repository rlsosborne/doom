#ifndef _doom_display_h_
#define _doom_display_h_

#include <stdint.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_BPP 8

#ifdef __XC__
interface uint_ptr_tx_slave;
interface uint_ptr_rx;

interface doom_display {
  [[notification]] slave void vblank();
  [[clears_notification]] void clear_vblank();
  uint16_t * unsafe get_palette_();
  uint8_t * unsafe get_frame_();
};

extends client interface doom_display : {
  void set_palette(client interface doom_display self, const uint16_t new_palette[256]);
  void write(client interface doom_display self, const uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT]);
  void read(client interface doom_display self, uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT]);
}

void doom_display(server interface doom_display screen,
                  client interface uint_ptr_tx_slave to_lcd,
                  client interface uint_ptr_rx from_lcd);

void doom_display_set_pointer(client interface doom_display * movable display);
#endif

#ifdef __cplusplus
extern "C" {
#endif
void doom_display_set_palette(const uint16_t new_palette[256]);
void doom_display_write(const uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT]);
void doom_display_read(uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT]);
#ifdef __cplusplus
}
#endif

#endif //_doom_display_h_
