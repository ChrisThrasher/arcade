add_executable(cube_timer main.cpp Scramble.cpp Timer.cpp)
target_link_libraries(cube_timer PRIVATE cxxcurses::cxxcurses)
install(TARGETS cube_timer)
