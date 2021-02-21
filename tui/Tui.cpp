#include <Tui/Tui.h>

namespace tui {

void Init()
{
    initscr();
    cbreak();
    noecho();
    clear();
    keypad(stdscr, TRUE);
    std::atexit([]() { endwin(); });
}

void Print(int row, int col, const std::string& text, int color)
{
    attron(color);
    mvaddstr(row, col, text.c_str());
    attroff(color);
}

}