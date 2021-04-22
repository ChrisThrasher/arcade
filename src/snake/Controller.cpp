#include "Controller.h"

#include <Tui/Tui.h>

Controller::Controller()
{
    tui::init();
    timeout(50);
}

Controller::~Controller()
{
    tui::draw(22, 0, "Game over.");
    tui::wait_for('q');
}

void Controller::cycle()
{
    get_input();
    draw();
}

void Controller::get_input()
{
    switch (getch()) {
    case KEY_UP:
        m_game.up();
        break;
    case KEY_DOWN:
        m_game.down();
        break;
    case KEY_LEFT:
        m_game.left();
        break;
    case KEY_RIGHT:
        m_game.right();
        break;
    case 'q':
        m_running = false;
        return;
    default:
        m_game.cycle();
        break;
    }

    m_running = m_game.running();
}

void Controller::draw()
{
    clear();

    const auto& board = m_game.board();

    size_t row = 0;
    for (; row < board.size(); ++row) {
        for (size_t col = 0; col < board[row].size(); ++col) {
            switch (board[row][col]) {
            case Game::Tile::EMPTY:
                tui::draw(row, col * 2, ".");
                break;
            case Game::Tile::SNAKE:
                tui::draw(row, col * 2, "0", tui::green);
                break;
            case Game::Tile::FRUIT:
                tui::draw(row, col * 2, "X", tui::red);
                break;
            }
        }
    }

    tui::draw(++row, 0, "Score: " + std::to_string(m_game.score()));

    refresh();
}
