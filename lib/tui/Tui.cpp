#include <Tui/Tui.h>

namespace tui {

int white = 0;
int black = 0;
int red = 0;
int yellow = 0;
int green = 0;
int cyan = 0;
int blue = 0;
int magenta = 0;

void Init()
{
    initscr();
    cbreak();
    noecho();
    clear();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    use_default_colors();

    init_pair(1, COLOR_WHITE, -1);
    init_pair(2, COLOR_BLACK, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_GREEN, -1);
    init_pair(6, COLOR_CYAN, -1);
    init_pair(7, COLOR_BLUE, -1);
    init_pair(8, COLOR_MAGENTA, -1);

    white = COLOR_PAIR(1);
    black = COLOR_PAIR(2);
    red = COLOR_PAIR(3);
    yellow = COLOR_PAIR(4);
    green = COLOR_PAIR(5);
    cyan = COLOR_PAIR(6);
    blue = COLOR_PAIR(7);
    magenta = COLOR_PAIR(8);

    std::atexit([]() { endwin(); });
}

void WaitFor(char c)
{
    while (getch() != c) { };
}

}