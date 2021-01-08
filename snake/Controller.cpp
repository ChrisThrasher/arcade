#include "Controller.h"

#include <ncurses.h>

#include <iostream>
#include <sstream>

Controller::Controller()
{
    initscr();
    cbreak();
    noecho();
    clear();
    timeout(50);
    keypad(stdscr, TRUE);
}

Controller::~Controller()
{
    endwin();
    std::cout << "Score: " << m_game.Score() << '\n';
}

void Controller::Cycle()
{
    GetInput();
    Draw();
}

bool Controller::Running() { return m_running; }

void Controller::GetInput()
{
    switch (getch())
    {
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

    std::stringstream out;
    for (auto& row : m_game.Board())
    {
        for (auto& tile : row)
        {
            switch (tile)
            {
            case Game::Tile::EMPTY:
                out << '.';
                break;
            case Game::Tile::SNAKE:
                out << '0';
                break;
            case Game::Tile::FRUIT:
                out << 'X';
                break;
            }
            out << ' ';
        }
        out << '\n';
    }
    out << '\n';
    out << "Score: " << m_game.Score() << '\n';

    mvaddstr(0, 0, out.str().c_str());
    refresh();
}
