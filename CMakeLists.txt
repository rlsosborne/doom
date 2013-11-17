cmake_minimum_required(VERSION 2.8.12)
project(lsdldoom)

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
  )

include(TestBigEndian)
include(CheckIncludeFiles)
include(CheckSymbolExists)

test_big_endian(__BIG_ENDIAN__)
check_include_files("linux/joystick.h" HAVE_LINUX_JOYSTICK_H)
check_include_files("sys/filio.h" HAVE_SYS_FILIO_H)
check_include_files("sys/ioctl.h" HAVE_SYS_IOCTL_H)
check_symbol_exists(strcasecmp strings.h LSDLDOOM_HAVE_STRCASECMP)
check_symbol_exists(socket "sys/socket.h" HAVE_NET)
check_symbol_exists(inet_aton "arpa/inet.h" HAVE_INET_ATON)
set(DOOMWADDIR "${CMAKE_INSTALL_PREFIX}/share/games/doom")
set(SNDSERV_PATH "")
if (NOT "${SNDSERV_PATH}" MATCHES "")
  set(HAVE_SNDSERV_PATH True)
endif()
set(MUSSERV_PATH "")
if (NOT "${MUSSERV_PATH}" MATCHES "")
  set(HAVE_MUSSERV_PATH True)
endif()
set(LSDLDOOM_VERSION_MAJOR 1)
set(LSDLDOOM_VERSION_MINOR 5)
set(LSDLDOOM_VERSION_TWEAK "")
set(
  CPACK_PACKAGE_VERSION
  "${LSDLDOOM_VERSION_MAJOR}.${LSDLDOOM_VERSION_MINOR}${LSDLDOOM_VERSION_TWEAK}")
option(HIGHRES "High resolution support" On)
option(RANGECHECK "Internal range checking" Off)
option(INSTRUMENTED "Real-time memory allocation statistics" Off)
option(CHECKHEAP "Exhaustively run memory checks" Off)
option(ZONEIDCHECK "Perform id checks on zone blocks" On)
option(SIMPLECHECKS "Quick checks" On)
option(TIMEDIAG "Lumps locked for long periods of time are reported" Off)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX True)
endif()
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "i686")
  set(I386 True)
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_subdirectory(data)
add_subdirectory(src)
add_subdirectory(doc)
install(FILES AUTHORS COPYING README DESTINATION share/doc/lsdldoom)

include(CPack)
