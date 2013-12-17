#include "get_time.h"

uint64_t get_time_uint64()
{
  timer t;
  static uint64_t time = 0;
  unsigned now;
  t :> now;
  time += (now - (uint32_t)time);
  return time;
}
