#include "Board.h"

#include <Tui/Tui.h>

#include <iomanip>
#include <iostream>
#include <sstream>

auto Draw(const Board& board) -> std::string;

int main()
{
    tui::Init();

    Board board;

    bool running = true;
    while (running) {
        clear();
        mvaddstr(1, 0, Draw(board).c_str());

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
            running = false;
            break;
        }

        switch (board.GameState()) {
        case Board::State::IN_PROGRESS:
            break;
        case Board::State::SUCCESS:
            running = false;
            std::cout << Draw(board);
            std::cout << "You win!\n";
            break;
        case Board::State::FAILURE:
            running = false;
            std::cout << Draw(board);
            std::cout << "Game over.\n";
            break;
        }
    }
}

auto Draw(const Board& board) -> std::string
{
    std::stringstream out;
    out << "Score: " << board.Score() << "\n\n";

    out << std::setfill(' ');
    for (const auto& row : board.Data()) {
        out << "---------------------\n";
        for (const auto& cell : row) {
            out << '|';
            out << std::right << std::setw(4);
            if (cell != 0)
                out << cell;
            else
                out << ' ';
        }
        out << "|\n";
    }
    out << "---------------------\n\n";

    out << "q: Quit\n";
    out << "n: New game\n\n";

    return out.str();
}