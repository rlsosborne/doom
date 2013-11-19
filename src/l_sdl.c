#include <stdlib.h>
#ifndef __XMOS__
#include "SDL.h"
#endif
#include "l_sdl.h"

void I_ShutdownSDL(void)
{
	//SDL_Quit();
	return;
}

void I_InitSDL(void)
{
        atexit(I_ShutdownSDL);
        return;
}
