cmake_minimum_required(VERSION 3.22)
project(arcade CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(cxxcurses
    GIT_REPOSITORY https://github.com/hjaremko/cxxcurses.git
    GIT_TAG master)
FetchContent_MakeAvailable(cxxcurses)

add_subdirectory(src)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.hpp *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
    COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
