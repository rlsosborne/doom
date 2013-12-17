#include "doom_display.h"
#include "ptr_buffers.h"
#include "lcd.h"
#include <string.h>
#include <stdint.h>

#define HORIZONTAL_OFFSET ((LCD_WIDTH - SCREEN_WIDTH) / 2)
#define VERTICAL_OFFSET ((LCD_HEIGHT - SCREEN_HEIGHT) / 2)

// TODO get rid of this.
static void movable_memset(char p[n], int c, size_t n)
{
  memset(p, c, n);
}

void doom_display(server interface doom_display screen,
                  client interface uint_ptr_tx_slave to_lcd,
                  client interface uint_ptr_rx from_lcd)
{
  static uint16_t palette[256] = {0};
  static uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};
  static unsigned row0[LCD_ROW_WORDS] = {0};
  static unsigned row1[LCD_ROW_WORDS] = {0};
  static unsigned row2[LCD_ROW_WORDS] = {0};
  const unsigned row_bytes = sizeof(row0);
  unsigned * movable row = row0;
  unsigned * movable row1ptr = row1;
  unsigned * movable row2ptr = row2;

  // Start things off.
  to_lcd.push(move(row1ptr));
  to_lcd.push(move(row2ptr));
  unsigned row_number = 3;
  while (1) {
    select {
    case screen.get_palette_() -> uint16_t * unsafe p:
      unsafe {
        p = (uint16_t * unsafe)palette;
      }
      break;
    case screen.get_frame_() -> uint8_t * unsafe p:
      unsafe {
        p = (uint8_t * unsafe)frame;
      }
      break;
    case screen.clear_vblank():
      break;
    case to_lcd.ready():
      unsigned * movable next_row;
      next_row = from_lcd.pop();
      to_lcd.push(move(row));
      row = move(next_row);
      if (row_number == LCD_HEIGHT) {
        screen.vblank();
        row_number = 0;
      }
      if (row_number >= VERTICAL_OFFSET &&
          row_number < VERTICAL_OFFSET + SCREEN_HEIGHT) {
        uint16_t (& restrict dst)[SCREEN_WIDTH] =
          (uint16_t * movable)row + HORIZONTAL_OFFSET;
        unsigned y = (row_number - VERTICAL_OFFSET);
        for (unsigned i = 0; i < SCREEN_WIDTH; i++) {
          dst[i] = palette[frame[i + y * SCREEN_WIDTH]];
        }
      } else {
        if (row_number >= VERTICAL_OFFSET + SCREEN_HEIGHT &&
            row_number < VERTICAL_OFFSET + SCREEN_HEIGHT + 3) {
          movable_memset((char * movable)row, 0, row_bytes);
        }
      }
      ++row_number;
      break;
    }
  }
}

extends client interface doom_display : {
  void set_palette(client interface doom_display self, const uint16_t new_palette[256]) {
    memcpy(self.get_palette_(), new_palette, sizeof(new_palette));
  }
  void write(client interface doom_display self, const uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT]) {
    select { case self.vblank(): break; }
    memcpy(self.get_frame_(), frame, sizeof(frame));
    self.clear_vblank();
  }
  void read(client interface doom_display self, uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT]) {
    memcpy(frame, self.get_frame_(), sizeof(frame));
  }
}

static client interface doom_display * movable display_ptr;

void doom_display_set_pointer(client interface doom_display * movable display)
{
  display_ptr = move(display);
}

void doom_display_set_palette(const uint16_t new_palette[256])
{
  display_ptr->set_palette(new_palette);
}

void doom_display_write(const uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT])
{
  display_ptr->write(frame);
}

void doom_display_read(uint8_t frame[SCREEN_WIDTH * SCREEN_HEIGHT])
{
  display_ptr->read(frame);
}
