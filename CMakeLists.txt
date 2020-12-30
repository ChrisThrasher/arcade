cmake_minimum_required(VERSION 3.5)
project(twentyfortyeight CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses)
add_library(ncurses INTERFACE)
target_include_directories(ncurses SYSTEM INTERFACE ${CURSES_INCLUDE_DIRS})
target_link_libraries(ncurses INTERFACE ${CURSES_LIBRARIES})

add_library(board src/Board.cpp)
target_include_directories(board PUBLIC include)
target_compile_options(board PUBLIC -Werror -Wall -Wextra -Wpedantic -Wshadow)

add_executable(twentyfortyeight src/TwentyFortyEight.cpp)
target_link_libraries(twentyfortyeight PRIVATE board ncurses)
