#ifndef __COMPILER_H__
#define __COMPILER_H__

#if defined(__XMOS__) && defined(XCC_MAJOR_VERSION)
#define OVERLAY __attribute__((overlay))
#else
#define OVERLAY
#endif

#endif // __COMPILER_H__
