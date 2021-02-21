#include "ConnectFour.h"

#include <Tui/Tui.h>

#include <algorithm>
#include <iostream>
#include <sstream>

void Draw(ConnectFour game, int column)
{
    clear();

    auto board = game.Board();
    for (size_t row = 0; row < 6; ++row) {
        for (size_t col = 0; col < 7; ++col) {
            switch (board[col][row]) {
            case Tile::EMPTY:
                tui::Print(6 - row, col * 2, "_");
                break;
            case Tile::RED:
                tui::Print(6 - row, col * 2, "O", COLOR_PAIR(1));
                break;
            case Tile::YEL:
                tui::Print(6 - row, col * 2, "O", COLOR_PAIR(2));
                break;
            }
        }
    }

    switch (game.ActiveTile()) {
    case Tile::EMPTY:
        break;
    case Tile::RED:
        tui::Print(7, column * 2, "^", COLOR_PAIR(1));
        break;
    case Tile::YEL:
        tui::Print(7, column * 2, "^", COLOR_PAIR(2));
        break;
    }

    tui::Print(8, 0, "Press q to exit");

    refresh();
}

int main()
{
    tui::Init();

    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_YELLOW, -1);

    ConnectFour game;
    while (game.Running()) {
        static int column = 3;

        Draw(game, column);

        switch (getch()) {
        case KEY_LEFT:
            column = std::max(0, column - 1);
            break;
        case KEY_RIGHT:
            column = std::min(6, column + 1);
            break;
        case KEY_DOWN:
            game.Add(column);
            break;
        case 'q':
            return 0;
        }
    }

    Draw(game, -1);
    tui::Print(10, 0, "Game over");
    while (getch() != 'q') { }
}
