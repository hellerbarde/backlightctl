# CMakeLists.txt for backlightctl
cmake_minimum_required(VERSION 2.6)
project(BacklightCtl)

add_executable(backlightctl backlightctl.c)

install(TARGETS backlightctl DESTINATION bin)
install(FILES backlightctl.conf DESTINATION /etc)