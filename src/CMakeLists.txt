find_package(SDL2 REQUIRED)

include(CheckCCompilerFlag)

if(${HAVE_NET})
  set(NET_CLIENT_SRC d_client.cpp l_udp.cpp)
else()
  set(NET_CLIENT_SRC d_client.cpp)
endif()

add_executable(
  lsdldoom
  am_map.cpp
  am_map.h
  d_deh.cpp
  d_deh.h
  d_englsh.h
  d_event.h
  d_items.cpp
  d_items.h
  d_main.cpp
  d_main.h
  d_net.h
  d_player.h
  d_think.h
  d_ticcmd.h
  doomdata.h
  doomdef.cpp
  doomdef.h
  doomstat.cpp
  doomstat.h
  doomtype.h
  dstrings.cpp
  dstrings.h
  f_finale.cpp
  f_finale.h
  f_wipe.cpp
  f_wipe.h
  g_game.cpp
  g_game.h
  hu_lib.cpp
  hu_lib.h
  hu_stuff.cpp
  hu_stuff.h
  i_joy.h
  i_main.h
  i_net.h
  i_network.h
  i_sound.h
  i_system.h
  i_video.h
  info.cpp
  info.h
  l_joy.cpp
  l_main.cpp
  l_sound_sdl.cpp
  l_system.cpp
  l_video_sdl.cpp
  lprintf.cpp
  lprintf.h
  m_argv.cpp
  m_argv.h
  m_bbox.cpp
  m_bbox.h
  m_cheat.cpp
  m_cheat.h
  m_fixed.h
  m_menu.cpp
  m_menu.h
  m_misc.cpp
  m_misc.h
  m_random.cpp
  m_random.h
  m_swap.h
  p_ceilng.cpp
  p_doors.cpp
  p_enemy.cpp
  p_enemy.h
  p_floor.cpp
  p_genlin.cpp
  p_inter.cpp
  p_inter.h
  p_lights.cpp
  p_map.cpp
  p_map.h
  p_maputl.cpp
  p_maputl.h
  p_mobj.cpp
  p_mobj.h
  p_plats.cpp
  p_pspr.cpp
  p_pspr.h
  p_saveg.cpp
  p_saveg.h
  p_setup.cpp
  p_setup.h
  p_sight.cpp
  p_spec.cpp
  p_spec.h
  p_switch.cpp
  p_telept.cpp
  p_tick.cpp
  p_tick.h
  p_user.cpp
  p_user.h
  protocol.h
  qmus2mid.cpp
  qmus2mid.h
  r_bsp.cpp
  r_bsp.h
  r_data.cpp
  r_data.h
  r_defs.h
  r_draw.cpp
  r_draw.h
  r_main.cpp
  r_main.h
  r_plane.cpp
  r_plane.h
  r_segs.cpp
  r_segs.h
  r_sky.cpp
  r_sky.h
  r_state.h
  r_things.cpp
  r_things.h
  s_sound.cpp
  s_sound.h
  sounds.cpp
  sounds.h
  st_lib.cpp
  st_lib.h
  st_stuff.cpp
  st_stuff.h
  tables.cpp
  tables.h
  v_video.cpp
  v_video.h
  version.cpp
  version.h
  w_wad.cpp
  w_wad.h
  wi_stuff.cpp
  wi_stuff.h
  z_bmalloc.cpp
  z_bmalloc.h
  z_zone.cpp
  z_zone.h
  ${NET_CLIENT_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/../config.h
)

add_executable(
  lsdldoom_game_server
  d_server.cpp
  l_udp.cpp
  protocol.h
  l_system.cpp)

set_property(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/../config.h PROPERTY GENERATED)

target_link_libraries(lsdldoom ${SDL2_LIBRARIES} m)
target_link_libraries(lsdldoom_game_server ${SDL2_LIBRARIES} m)
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(
  lsdldoom PUBLIC
  ${SDL2_DEFINITIONS} HAVE_CONFIG_H)
target_compile_definitions(
  lsdldoom_game_server PUBLIC
  ${SDL2_DEFINITIONS} HAVE_CONFIG_H)
if (${HAVE_NET})
  target_compile_definitions(lsdldoom PRIVATE HAVE_NET HAVE_BSD_NET)
  target_compile_definitions(lsdldoom_game_server PRIVATE HAVE_NET HAVE_BSD_NET)
endif()
if (${HAVE_MIXER})
  target_link_libraries(lsdldoom ${SDL2_MIXER_LIBRARIES})
  include_directories(${SDL2_MIXER_INCLUDE_DIRS})
endif()
check_c_compiler_flag(-fno-strict-aliasing HAS_NO_STRICT_ALIASING)
if (${HAS_NO_STRICT_ALIASING})
  add_definitions(-fno-strict-aliasing)
endif()

install(TARGETS lsdldoom lsdldoom_game_server DESTINATION games)
