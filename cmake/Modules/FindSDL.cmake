# Locate SDL
# This module defines
#  SDL_FOUND - System has SDL
#  SDL_CONFIG_EXECUTABLE - The sdl-config executable
#  SDL_INCLUDE_DIRS - SDL include directories
#  SDL_DEFINITIONS - SDL compiler definitions
#  SDL_LIBRARIES - Libraries needed to link against SDL

find_program(SDL_CONFIG_EXECUTABLE
  NAMES sdl-config
  DOC "sdl-config executable")

include(FindPackageHandleStandardArgs)
# Sets SDL_FOUND
find_package_handle_standard_args(
  SDL DEFAULT_MSG SDL_CONFIG_EXECUTABLE)

if (SDL_FOUND)
  execute_process(
    COMMAND ${SDL_CONFIG_EXECUTABLE} --cflags
    OUTPUT_VARIABLE SDL_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${SDL_CONFIG_EXECUTABLE} --libs
    OUTPUT_VARIABLE SDL_LIBRARIES
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Extract include directories / defines
  string(REPLACE " " ";" SDL_CFLAGS_LIST ${SDL_CFLAGS})
  foreach(FLAG ${SDL_CFLAGS_LIST})
    if(${FLAG} MATCHES "^-I")
      STRING(REGEX REPLACE "^-I" "" FLAG ${FLAG})
      list(APPEND SDL_INCLUDE_DIRS ${FLAG})
    elseif(${FLAG} MATCHES "^-D")
      STRING(REGEX REPLACE "^-D" "" FLAG ${FLAG})
      list(APPEND SDL_DEFINITIONS ${FLAG})
    endif()
  endforeach()
endif()

mark_as_advanced(SDL_CONFIG_EXECUTABLE)
