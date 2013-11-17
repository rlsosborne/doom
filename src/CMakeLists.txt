find_package(SDL2 REQUIRED)

include(CheckCCompilerFlag)

if(${HAVE_NET})
  set(NET_CLIENT_SRC d_client.c l_udp.c)
else()
  set(NET_CLIENT_SRC d_client.c)
endif()

add_executable(
  lsdldoom
  am_map.c
  am_map.h
  d_deh.c
  d_deh.h
  d_englsh.h
  d_event.h
  d_items.c
  d_items.h
  d_main.c
  d_main.h
  d_net.h
  d_player.h
  d_think.h
  d_ticcmd.h
  doomdata.h
  doomdef.c
  doomdef.h
  doomstat.c
  doomstat.h
  doomtype.h
  drawasm.h
  dstrings.c
  dstrings.h
  f_finale.c
  f_finale.h
  f_wipe.c
  f_wipe.h
  g_game.c
  g_game.h
  hu_lib.c
  hu_lib.h
  hu_stuff.c
  hu_stuff.h
  i_joy.h
  i_main.h
  i_net.h
  i_network.h
  i_sound.h
  i_system.h
  i_video.h
  info.c
  info.h
  l_joy.c
  l_main.c
  l_sdl.c
  l_sdl.h
  l_sound_sdl.c
  l_system.c
  l_video_sdl.c
  lprintf.c
  lprintf.h
  m_argv.c
  m_argv.h
  m_bbox.c
  m_bbox.h
  m_cheat.c
  m_cheat.h
  m_fixed.h
  m_menu.c
  m_menu.h
  m_misc.c
  m_misc.h
  m_random.c
  m_random.h
  m_swap.h
  p_ceilng.c
  p_doors.c
  p_enemy.c
  p_enemy.h
  p_floor.c
  p_genlin.c
  p_inter.c
  p_inter.h
  p_lights.c
  p_map.c
  p_map.h
  p_maputl.c
  p_maputl.h
  p_mobj.c
  p_mobj.h
  p_plats.c
  p_pspr.c
  p_pspr.h
  p_saveg.c
  p_saveg.h
  p_setup.c
  p_setup.h
  p_sight.c
  p_spec.c
  p_spec.h
  p_switch.c
  p_telept.c
  p_tick.c
  p_tick.h
  p_user.c
  p_user.h
  protocol.h
  qmus2mid.c
  qmus2mid.h
  r_bsp.c
  r_bsp.h
  r_data.c
  r_data.h
  r_defs.h
  r_draw.c
  r_draw.h
  r_main.c
  r_main.h
  r_plane.c
  r_plane.h
  r_segs.c
  r_segs.h
  r_sky.c
  r_sky.h
  r_state.h
  r_things.c
  r_things.h
  s_sound.c
  s_sound.h
  sounds.c
  sounds.h
  st_lib.c
  st_lib.h
  st_stuff.c
  st_stuff.h
  tables.c
  tables.h
  v_video.c
  v_video.h
  version.c
  version.h
  w_wad.c
  w_wad.h
  wi_stuff.c
  wi_stuff.h
  z_bmalloc.c
  z_bmalloc.h
  z_zone.c
  z_zone.h
  ${NET_CLIENT_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/../config.h
)

add_executable(
  lsdldoom_game_server
  d_server.c
  l_udp.c
  protocol.h
  l_system.c)

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
check_c_compiler_flag(-fno-strict-aliasing HAS_NO_STRICT_ALIASING)
if (${HAS_NO_STRICT_ALIASING})
  add_definitions(-fno-strict-aliasing)
endif()

install(TARGETS lsdldoom lsdldoom_game_server DESTINATION games)
