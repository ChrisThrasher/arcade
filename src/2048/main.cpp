#include "Board.h"

#include <cxxcurses/cxxcurses.hpp>

#include <cmath>
#include <iomanip>
#include <map>
#include <sstream>

static const auto& g_win = cxxcurses::terminal::main_win;

void draw(const Board& board);

int main()
{
    cxxcurses::terminal init;

    Board board;

    for (;;) {
        clear();
        draw(board);

        switch (getch()) {
        case KEY_UP:
            board.up();
            break;
        case KEY_DOWN:
            board.down();
            break;
        case KEY_LEFT:
            board.left();
            break;
        case KEY_RIGHT:
            board.right();
            break;
        case 'n':
            board.reset();
            break;
        case 'q':
            return 0;
            break;
        }

        switch (board.game_state()) {
        case Board::State::IN_PROGRESS:
            break;
        case Board::State::SUCCESS:
            draw(board);
            g_win << cxxcurses::format(14, 0)("You win!");
            while (getch() != 'q') { };
            return 0;
        case Board::State::FAILURE:
            draw(board);
            g_win << cxxcurses::format(14, 0)("Game over.");
            while (getch() != 'q') { };
            return -1;
        }
    }
}

void draw(const Board& board)
{
    static const std::map<size_t, std::string> colors
        = { { 0, "{}" },   { 2, "{}" },    { 4, "{y}" },   { 8, "{r}" },   { 16, "{m}" },   { 32, "{b}" },
            { 64, "{c}" }, { 128, "{g}" }, { 256, "{y}" }, { 512, "{r}" }, { 1024, "{m}" }, { 2048, "{b}" } };

    const auto& data = board.data();

    size_t row = 0;
    for (; row < data.size(); ++row) {
        g_win << cxxcurses::format(row * 2, 0)("---------------------\n");
        size_t col = 0;
        for (; col < data[row].size(); ++col) {
            g_win << cxxcurses::format(row * 2 + 1, col * 5)("|");
            std::stringstream out;
            out << std::setfill(' ') << std::right << std::setw(4);
            const auto& cell = data[row][col];
            if (cell != 0)
                out << cell;
            else
                out << ' ';
            g_win << cxxcurses::format(row * 2 + 1, col * 5 + 1)(colors.at(cell), out.str());
        }
        g_win << cxxcurses::format(row * 2 + 1, col * 5)("|");
    }
    g_win << cxxcurses::format(row * 2, 0)("---------------------\n");

    g_win << cxxcurses::format(row * 2 + 1, 0)("Score: " + std::to_string(board.score()));
    g_win << cxxcurses::format(row * 2 + 3, 0)("q: Quit");
    g_win << cxxcurses::format(row * 2 + 4, 0)("n: New game");
}
