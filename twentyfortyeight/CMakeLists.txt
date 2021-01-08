add_library(board src/Board.cpp)
target_include_directories(board PUBLIC include)
target_compile_options(board PUBLIC -Werror -Wall -Wextra -Wpedantic -Wshadow)

add_executable(twentyfortyeight src/TwentyFortyEight.cpp)
target_link_libraries(twentyfortyeight PRIVATE board ncurses)