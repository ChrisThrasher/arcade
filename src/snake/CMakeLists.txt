add_executable(snake main.cpp Controller.cpp Game.cpp)
target_link_libraries(snake PRIVATE cxxcurses::cxxcurses)
install(TARGETS snake)
