// Just enough to avoid undefined references.

#include "doomtype.h"

void (*R_DrawColumn)(void);
void (*R_DrawTLColumn)(void);

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
  __builtin_trap();
}

void I_StartFrame (void)
{
  __builtin_trap();
}

void I_ShutdownGraphics(void)
{
  __builtin_trap();
}

void I_UpdateNoBlit (void)
{
  __builtin_trap();
}

void I_FinishUpdate (void)
{
  __builtin_trap();
}

void I_ReadScreen (byte* scr)
{
  __builtin_trap();
}

void I_SetPalette (int pal)
{
  __builtin_trap();
}

void I_PreInitGraphics(void)
{
  __builtin_trap();
}

void I_SetRes(unsigned int width, unsigned int height)
{
  __builtin_trap();
}

void I_InitGraphics(void)
{
  __builtin_trap();
}

