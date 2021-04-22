#include "ConnectFour.h"

#include <Tui/Tui.h>

#include <algorithm>

void draw(ConnectFour game, int column)
{
    clear();

    auto board = game.board();
    for (size_t row = 0; row < 6; ++row) {
        for (size_t col = 0; col < 7; ++col) {
            switch (board[col][row]) {
            case Tile::EMPTY:
                tui::draw(6 - row, col * 2, "_");
                break;
            case Tile::RED:
                tui::draw(6 - row, col * 2, "O", tui::red);
                break;
            case Tile::YEL:
                tui::draw(6 - row, col * 2, "O", tui::yellow);
                break;
            }
        }
    }

    switch (game.active_tile()) {
    case Tile::EMPTY:
        break;
    case Tile::RED:
        tui::draw(7, column * 2, "^", tui::red);
        break;
    case Tile::YEL:
        tui::draw(7, column * 2, "^", tui::yellow);
        break;
    }

    tui::draw(8, 0, "Press q to exit");

    refresh();
}

int main()
{
    tui::init();

    ConnectFour game;
    while (game.running()) {
        static int column = 3;

        draw(game, column);

        switch (getch()) {
        case KEY_LEFT:
            column = std::max(0, column - 1);
            break;
        case KEY_RIGHT:
            column = std::min(6, column + 1);
            break;
        case KEY_DOWN:
            game.add(column);
            break;
        case 'q':
            return 0;
        }
    }

    draw(game, -1);
    tui::draw(10, 0, "Game over");
    tui::wait_for('q');
}
