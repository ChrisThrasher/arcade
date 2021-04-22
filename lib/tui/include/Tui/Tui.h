#pragma once

#include <ncurses.h>

#include <string>

namespace tui {

extern int white;
extern int black;
extern int red;
extern int yellow;
extern int green;
extern int cyan;
extern int blue;
extern int magenta;

void init();
void wait_for(char c);

template <typename T, typename U>
void draw(T row, U col, const std::string& text, int color = 0)
{
    if (color == 0) {
        mvaddstr(static_cast<int>(row), static_cast<int>(col), text.c_str());
    } else {
        attron(color);
        mvaddstr(static_cast<int>(row), static_cast<int>(col), text.c_str());
        attroff(color);
    }
}

}