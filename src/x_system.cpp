#include "compiler.h"
#include <stdio.h>

#include "xs1.h"
#include "get_time.h"

#include "i_system.h"
#include "doomtype.h"
#include "doomdef.h"

#include "i_system.h"

OVERLAY int I_GetTime_RealTime (void)
{
  return (get_time_uint64() * TICRATE) / XS1_TIMER_HZ;
}

OVERLAY unsigned long I_GetRandomTimeSeed(void)
{
  return get_time_uint64();
}

OVERLAY const char* I_SigString(char* buf, size_t sz, int signum)
{
  sprintf(buf,"signal %d",signum);
  return buf;
}

int I_FileExists(const char *path)
{
  return I_FileIsReadable(path);
}

int I_FileIsReadable(const char *path)
{
  FILE *fp = fopen(path, "r");
  if (!fp)
    return 0;
  fclose(fp);
  return 1;
}

int I_IsATerminal(int fd)
{
  return 0;
}

#define HEAP_MB 6

static byte heap[HEAP_MB*1024*1024];

byte *I_ZoneBase(int *size)
{
  *size = HEAP_MB * 1024 * 1024;
  return heap;
}
