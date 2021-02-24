add_executable(connect_four main.cpp ConnectFour.cpp)
target_link_libraries(connect_four PRIVATE tui)
install(TARGETS connect_four)
