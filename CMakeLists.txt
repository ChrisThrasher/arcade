cmake_minimum_required(VERSION 3.10)
project(arcade CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow)

add_subdirectory(connect_four)
add_subdirectory(cube_timer)
add_subdirectory(snake)
add_subdirectory(tui)
add_subdirectory(2048)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.h *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(tidy
    COMMAND clang-tidy -p build/compile_commands.json `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
