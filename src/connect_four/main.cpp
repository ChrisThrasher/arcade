#include "ConnectFour.h"

#include <cxxcurses/cxxcurses.hpp>

#include <algorithm>

static const auto& g_win = cxxcurses::terminal::main_win;

void draw(ConnectFour game, int column)
{
    clear();

    auto board = game.board();
    for (size_t row = 0; row < 6; ++row) {
        for (size_t col = 0; col < 7; ++col) {
            switch (board[col][row]) {
            case Tile::EMPTY:
                g_win << cxxcurses::format(6 - row, col * 2)("_");
                break;
            case Tile::RED:
                g_win << cxxcurses::format(6 - row, col * 2)("{r}", "O");
                break;
            case Tile::YEL:
                g_win << cxxcurses::format(6 - row, col * 2)("{y}", "O");
                break;
            }
        }
    }

    switch (game.active_tile()) {
    case Tile::EMPTY:
        break;
    case Tile::RED:
        g_win << cxxcurses::format(7, column * 2)("{r}", "^");
        break;
    case Tile::YEL:
        g_win << cxxcurses::format(7, column * 2)("{y}", "^");
        break;
    }

    g_win << cxxcurses::format(8, 0)("Press q to exit");

    refresh();
}

int main()
{
    cxxcurses::terminal init;
    keypad(stdscr, TRUE);

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
    g_win << cxxcurses::format(10, 0)("Game over");
    while (getch() != 'q') { };
}
