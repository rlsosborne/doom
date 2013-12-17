#include "i_video.h"
#include "doomstat.h"
#include "doomtype.h"
#include "lprintf.h"
#include "w_wad.h"
#include "v_video.h"
#include "z_zone.h"
#include "doom_display.h"

int use_vsync = 0; // Included not to break m_misc, but not relevant to SDL
int leds_always_off = 0; // Expected by m_misc, not relevant

int I_DoomCode2ScanCode(int c)
{
  __builtin_trap();
}

int I_ScanCode2DoomCode(int c)
{
  __builtin_trap();
}

void I_StartTic (void)
{
}

void I_StartFrame (void)
{
}

void I_ShutdownGraphics(void)
{
}

void I_UpdateNoBlit (void)
{
}

static inline boolean I_SkipFrame(void)
{
  static int frameno;

  frameno++;
  switch (gamestate) {
#pragma fallthrough
  case GS_LEVEL:
    if (!paused)
      return false;
  default:
    // Skip odd frames
    return (frameno & 1) ? true : false;
  }
}

void I_FinishUpdate (void)
{
  if (I_SkipFrame())
    return;

  doom_display_write(screens[0]);
}

void I_ReadScreen (byte* scr)
{
  doom_display_read(scr);
}

void I_SetPalette (int pal)
{
  static uint16_t *colours;
  static int cachedgamma;
  static size_t num_pals;

  if (colours == NULL || cachedgamma != usegamma) {
    int lump = W_GetNumForName("PLAYPAL");
    const byte *palette = W_CacheLumpNum(lump);
    const byte *const gtable = gammatable[cachedgamma = usegamma];
    int i;

    num_pals = W_LumpLength(lump) / (3*256);
    num_pals *= 256;

    if (!colours) {
      // First call - allocate and prepare colour array
      colours = malloc(sizeof(*colours) * num_pals);
    }

    // set the colormap entries
    for (i = 0 ; i < num_pals ; i++) {
      byte r = gtable[palette[0]];
      byte g = gtable[palette[1]];
      byte b = gtable[palette[2]];
      colours[i] = ((b >> 3) << 11) | ((g >> 2) << 5) | (r >> 3);
      palette += 3;
    }
  
    W_UnlockLumpNum(lump);
    num_pals /= 256;
  }

#ifdef RANGECHECK
  if (pal >= num_pals) 
    I_Error("I_UploadNewPalette: Palette number out of range (%d>=%d)", 
	    pal, (int)num_pals);
#endif

  // store the colors to the current display
  doom_display_set_palette(colours + 256 * pal);
}

void I_PreInitGraphics(void)
{
}

void I_SetRes(unsigned int width, unsigned int height)
{
  if (width != SCREEN_WIDTH || height != SCREEN_HEIGHT)
    __builtin_trap();
}

void I_InitGraphics(void)
{
  lprintf(LO_INFO,"I_InitGraphics: xCORE\n");
}

