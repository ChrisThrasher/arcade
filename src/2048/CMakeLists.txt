add_executable(2048 main.cpp Board.cpp)
target_link_libraries(2048 PRIVATE cxxcurses::cxxcurses)
install(TARGETS 2048)
