cmake_minimum_required(VERSION 3.5)
project(arcade CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses)
add_library(ncurses INTERFACE)
target_include_directories(ncurses SYSTEM INTERFACE ${CURSES_INCLUDE_DIRS})
target_link_libraries(ncurses INTERFACE ${CURSES_LIBRARIES})

add_subdirectory(twentyfortyeight)
