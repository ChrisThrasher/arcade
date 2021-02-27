#include "ConnectFour.h"

#include <Tui/Tui.h>

#include <algorithm>

void Draw(ConnectFour game, int column)
{
    clear();

    auto board = game.Board();
    for (size_t row = 0; row < 6; ++row) {
        for (size_t col = 0; col < 7; ++col) {
            switch (board[col][row]) {
            case Tile::EMPTY:
                tui::Draw(6 - row, col * 2, "_");
                break;
            case Tile::RED:
                tui::Draw(6 - row, col * 2, "O", tui::red);
                break;
            case Tile::YEL:
                tui::Draw(6 - row, col * 2, "O", tui::yellow);
                break;
            }
        }
    }

    switch (game.ActiveTile()) {
    case Tile::EMPTY:
        break;
    case Tile::RED:
        tui::Draw(7, column * 2, "^", tui::red);
        break;
    case Tile::YEL:
        tui::Draw(7, column * 2, "^", tui::yellow);
        break;
    }

    tui::Draw(8, 0, "Press q to exit");

    refresh();
}

int main()
{
    tui::Init();

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
    tui::Draw(10, 0, "Game over");
    tui::WaitFor('q');
}
