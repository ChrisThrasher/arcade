#include "Controller.h"

#include <Tui/Tui.h>

Controller::Controller()
{
    tui::Init();
    timeout(50);

    init_pair(2, COLOR_RED, -1);
    init_pair(1, COLOR_GREEN, -1);
}

Controller::~Controller()
{
    tui::Draw(22, 0, "Game over.");
    tui::WaitFor('q');
}

void Controller::Cycle()
{
    GetInput();
    Draw();
}

bool Controller::Running() { return m_running; }

void Controller::GetInput()
{
    switch (getch()) {
    case KEY_UP:
        m_game.Up();
        break;
    case KEY_DOWN:
        m_game.Down();
        break;
    case KEY_LEFT:
        m_game.Left();
        break;
    case KEY_RIGHT:
        m_game.Right();
        break;
    case 'q':
        m_running = false;
        return;
    default:
        m_game.Cycle();
        break;
    }

    m_running = m_game.Running();
}

void Controller::Draw()
{
    clear();

    const auto& board = m_game.Board();

    size_t row = 0;
    for (; row < board.size(); ++row) {
        for (size_t col = 0; col < board[row].size(); ++col) {
            switch (board[row][col]) {
            case Game::Tile::EMPTY:
                tui::Draw(row, col * 2, ".");
                break;
            case Game::Tile::SNAKE:
                tui::Draw(row, col * 2, "0", COLOR_PAIR(1));
                break;
            case Game::Tile::FRUIT:
                tui::Draw(row, col * 2, "X", COLOR_PAIR(2));
                break;
            }
        }
    }

    tui::Draw(++row, 0, "Score: " + std::to_string(m_game.Score()));

    refresh();
}
