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

void Init();
void Draw(int row, int col, const std::string& text, int color = 0);
void WaitFor(char c);

}