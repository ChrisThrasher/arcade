find_package(Curses REQUIRED)
add_library(ncurses INTERFACE)
target_include_directories(ncurses SYSTEM INTERFACE ${CURSES_INCLUDE_DIRS})
target_link_libraries(ncurses INTERFACE ${CURSES_LIBRARIES})

add_library(tui Tui.cpp)
target_include_directories(tui PUBLIC include)
target_link_libraries(tui PUBLIC ncurses)
