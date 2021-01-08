add_executable(snake Snake.cpp Controller.cpp Game.cpp)
target_link_libraries(snake PRIVATE ncurses)
