add_executable(cube_timer main.cpp Scramble.cpp Timer.cpp)
target_link_libraries(cube_timer PRIVATE tui)
install(TARGETS cube_timer)
