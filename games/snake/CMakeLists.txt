add_executable(snake main.cpp Controller.cpp Game.cpp)
target_link_libraries(snake PRIVATE tui)
install(TARGETS snake)
