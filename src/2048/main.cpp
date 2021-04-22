#include "Board.h"

#include <Tui/Tui.h>

#include <cmath>
#include <iomanip>
#include <map>
#include <sstream>

void draw(const Board& board);

int main()
{
    tui::init();

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
            tui::draw(14, 0, "You win!");
            tui::wait_for('q');
            return 0;
        case Board::State::FAILURE:
            draw(board);
            tui::draw(14, 0, "Game over.");
            tui::wait_for('q');
            return -1;
        }
    }
}

void draw(const Board& board)
{
    const auto& data = board.data();

    static const std::map<size_t, int> colors
        = { { 0, tui::white },    { 2, tui::white }, { 4, tui::yellow },     { 8, tui::red },
            { 16, tui::magenta }, { 32, tui::blue }, { 64, tui::cyan },      { 128, tui::green },
            { 256, tui::yellow }, { 512, tui::red }, { 1024, tui::magenta }, { 2048, tui::blue } };

    size_t row = 0;
    for (; row < data.size(); ++row) {
        tui::draw(row * 2, 0, "---------------------\n");
        size_t col = 0;
        for (; col < data[row].size(); ++col) {
            tui::draw(row * 2 + 1, col * 5, "|");
            std::stringstream out;
            out << std::setfill(' ') << std::right << std::setw(4);
            const auto& cell = data[row][col];
            if (cell != 0)
                out << cell;
            else
                out << ' ';
            tui::draw(row * 2 + 1, col * 5 + 1, out.str(), colors.at(cell));
        }
        tui::draw(row * 2 + 1, col * 5, "|");
    }
    tui::draw(row * 2, 0, "---------------------\n");

    tui::draw(row * 2 + 1, 0, "Score: " + std::to_string(board.score()));
    tui::draw(row * 2 + 3, 0, "q: Quit");
    tui::draw(row * 2 + 4, 0, "n: New game");
}
