#include "Board.h"

#include <Tui/Tui.h>

#include <cmath>
#include <iomanip>
#include <sstream>

void Draw(const Board& board);

int main()
{
    tui::Init();

    init_pair(1, -1, -1);
    init_pair(2, -1, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_RED, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_CYAN, -1);
    init_pair(7, COLOR_BLUE, -1);
    init_pair(8, COLOR_GREEN, -1);
    init_pair(9, COLOR_GREEN, -1);
    init_pair(10, COLOR_GREEN, -1);
    init_pair(11, COLOR_GREEN, -1);

    Board board;

    for (;;) {
        clear();
        Draw(board);

        switch (getch()) {
        case KEY_UP:
            board.Up();
            break;
        case KEY_DOWN:
            board.Down();
            break;
        case KEY_LEFT:
            board.Left();
            break;
        case KEY_RIGHT:
            board.Right();
            break;
        case 'n':
            board.Reset();
            break;
        case 'q':
            return 0;
            break;
        }

        switch (board.GameState()) {
        case Board::State::IN_PROGRESS:
            break;
        case Board::State::SUCCESS:
            Draw(board);
            tui::Draw(14, 0, "You win!");
            tui::WaitFor('q');
            return 0;
        case Board::State::FAILURE:
            Draw(board);
            tui::Draw(14, 0, "Game over.");
            tui::WaitFor('q');
            return -1;
        }
    }
}

void Draw(const Board& board)
{
    const auto& data = board.Data();

    size_t row = 0;
    for (; row < data.size(); ++row) {
        tui::Draw(row * 2, 0, "---------------------\n");
        size_t col = 0;
        for (; col < data[row].size(); ++col) {
            tui::Draw(row * 2 + 1, col * 5, "|");
            std::stringstream out;
            out << std::setfill(' ') << std::right << std::setw(4);
            auto& cell = data[row][col];
            if (cell != 0)
                out << cell;
            else
                out << ' ';
            tui::Draw(row * 2 + 1, col * 5 + 1, out.str(), COLOR_PAIR(static_cast<int>(std::log2(cell))));
        }
        tui::Draw(row * 2 + 1, col * 5, "|");
    }
    tui::Draw(row * 2, 0, "---------------------\n");

    tui::Draw(row * 2 + 1, 0, "Score: " + std::to_string(board.Score()));
    tui::Draw(row * 2 + 3, 0, "q: Quit");
    tui::Draw(row * 2 + 4, 0, "n: New game");
}