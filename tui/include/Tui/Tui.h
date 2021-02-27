#pragma once

#include <ncurses.h>

#include <string>

namespace tui {

void Init();
void Draw(int row, int col, const std::string& text, int color = 0);
void WaitFor(char c);

}