#include <Tui/Tui.h>

namespace tui {

void Init()
{
    initscr();
    cbreak();
    noecho();
    clear();
    keypad(stdscr, TRUE);
    curs_set(0);
    std::atexit([]() { endwin(); });
}

void Draw(int row, int col, const std::string& text, int color)
{
    if (color == 0) {
        mvaddstr(row, col, text.c_str());
    } else {
        attron(color);
        mvaddstr(row, col, text.c_str());
        attroff(color);
    }
}

void WaitFor(char c)
{
    while (getch() != c) { };
}

}