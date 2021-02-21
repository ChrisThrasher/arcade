#pragma once

#include <ncurses.h>

#include <string>

namespace tui {

void Init();
void Print(int row, int col, const std::string& text, int color = 0);

}