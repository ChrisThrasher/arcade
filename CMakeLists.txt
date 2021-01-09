cmake_minimum_required(VERSION 3.5)
project(arcade CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses)
add_library(ncurses INTERFACE)
target_include_directories(ncurses SYSTEM INTERFACE ${CURSES_INCLUDE_DIRS})
target_link_libraries(ncurses INTERFACE ${CURSES_LIBRARIES})

add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow)

add_subdirectory(snake)
add_subdirectory(2048)

add_custom_target(format
    COMMAND clang-format `git ls-files *.h *.cpp` -i
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(tidy
    COMMAND clang-tidy -p build/compile_commands.json `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
