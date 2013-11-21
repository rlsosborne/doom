// Just enough to avoid undefined references.

#include "sounds.h"
#include "doomtype.h"
#include <stddef.h>

#define NUM_CHANNELS		8

int snd_card = 1;
int mus_card = 1;
int detect_voices = 0;
int 		lengths[NUMSFX];
unsigned int	channelstep[NUM_CHANNELS];
unsigned int	channelstepremainder[NUM_CHANNELS];
unsigned char*	channels[NUM_CHANNELS];
unsigned char*	channelsend[NUM_CHANNELS];
int		channelstart[NUM_CHANNELS];
int 		channelhandles[NUM_CHANNELS];
int		channelids[NUM_CHANNELS];
int		steptable[256];
int		vol_lookup[128*256];
int*		channelleftvol_lookup[NUM_CHANNELS];
int*		channelrightvol_lookup[NUM_CHANNELS];

void*
getsfx
( const char*         sfxname,
  int*          len )
{
  __builtin_trap();
}

int
addsfx
( int		sfxid,
  int		volume,
  int		step,
  int		seperation )
{
  __builtin_trap();
}

void I_SetChannels()
{
  __builtin_trap();
}	

void I_SetSfxVolume(int volume)
{
  __builtin_trap();
}

int I_GetSfxLumpNum(sfxinfo_t* sfx)
{
  __builtin_trap();
}

int
I_StartSound
( int		id,
  int		vol,
  int		sep,
  int		pitch,
  int		priority )
{
  __builtin_trap();
}

void I_StopSound (int handle)
{
  __builtin_trap();
}

boolean I_SoundIsPlaying(int handle)
{
  __builtin_trap();
}

void
I_UpdateSoundParams
( int	handle,
  int	vol,
  int	sep,
  int	pitch)
{
  __builtin_trap();
}

void I_ShutdownSound(void)
{
  __builtin_trap();
}

void
I_InitSound()
{
  __builtin_trap();
}

void I_ShutdownMusic(void) 
{
  __builtin_trap();
}

void I_InitMusic(void)
{
  __builtin_trap();
}

void I_PlaySong(int handle, int looping)
{
  __builtin_trap();
}

void I_PauseSong (int handle)
{
  __builtin_trap();
}

void I_ResumeSong (int handle)
{
  __builtin_trap();
}

void I_StopSong(int handle)
{
  __builtin_trap();
}

void I_UnRegisterSong(int handle)
{
  __builtin_trap();
}

int I_RegisterSong(const void *data, size_t len)
{
  __builtin_trap();
}

void I_SetMusicVolume(int volume)
{
  __builtin_trap();
}
