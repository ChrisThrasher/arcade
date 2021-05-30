find_package(Curses REQUIRED)
add_library(Curses::ncurses INTERFACE IMPORTED)
target_include_directories(Curses::ncurses SYSTEM INTERFACE ${CURSES_INCLUDE_DIRS})
target_link_libraries(Curses::ncurses INTERFACE ${CURSES_LIBRARIES})

add_library(tui Tui.cpp)
target_include_directories(tui PUBLIC include)
target_link_libraries(tui PUBLIC Curses::ncurses)
