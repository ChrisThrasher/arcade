#include "Controller.h"

#include <cxxcurses/cxxcurses.hpp>

static const auto& g_win = cxxcurses::terminal::main_win;

Controller::Controller() { timeout(50); }

Controller::~Controller()
{
    g_win << cxxcurses::format(22, 0)("Game over.");
    while (getch() != 'q') { };
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
                g_win << cxxcurses::format(row, col * 2)(".");
                break;
            case Game::Tile::SNAKE:
                g_win << cxxcurses::format(row, col * 2)("{g}", "0");
                break;
            case Game::Tile::FRUIT:
                g_win << cxxcurses::format(row, col * 2)("{r}", "X");
                break;
            }
        }
    }

    g_win << cxxcurses::format(++row, 0)("Score: " + std::to_string(m_game.score()));

    refresh();
}
