cmake_minimum_required(VERSION 3.16)
project(arcade CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(cxxcurses
    GIT_REPOSITORY "https://github.com/ChrisThrasher/cxxcurses.git"
    GIT_TAG inline-free-functions)
FetchContent_MakeAvailable(cxxcurses)

add_subdirectory(src)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.h *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_custom_target(tidy
    COMMAND clang-tidy -p build/compile_commands.json `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
