#include "Game.h"

Game::Game()
{
    m_snake = {std::ref(m_board[m_head.first][m_head.second])};
    for (auto& tile : m_snake)
        tile.get() = Tile::SNAKE;
    AddFruit();
}

void Game::Cycle()
{
    switch (m_direction)
    {
    case Direction::UP:
        m_head.first = m_head.first == 0 ? m_size - 1 : m_head.first - 1;
        break;
    case Direction::DOWN:
        m_head.first = (m_head.first + 1) % m_size;
        break;
    case Direction::LEFT:
        m_head.second = m_head.second == 0 ? m_size - 1 : m_head.second - 1;
        break;
    case Direction::RIGHT:
        m_head.second = (m_head.second + 1) % m_size;
        break;
    case Direction::NONE:
        return;
    }

    auto& upcoming_tile = m_board[m_head.first][m_head.second];
    switch (upcoming_tile)
    {
    case Tile::SNAKE:
        m_running = false;
        break;
    case Tile::FRUIT:
        m_snake.push_front(upcoming_tile);
        m_snake.front().get() = Tile::SNAKE;
        AddFruit();
        ++m_score;
        break;
    case Tile::EMPTY:
        m_snake.push_front(upcoming_tile);
        m_snake.front().get() = Tile::SNAKE;
        m_snake.back().get() = Tile::EMPTY;
        m_snake.pop_back();
        break;
    }
}

void Game::AddFruit()
{
    auto row = m_distribution(m_rng);
    auto col = m_distribution(m_rng);
    while (m_board[row][col] == Tile::SNAKE)
    {
        row = m_distribution(m_rng);
        col = m_distribution(m_rng);
    }
    m_board[row][col] = Tile::FRUIT;
}

void Game::Up()
{
    if (m_direction != Direction::DOWN)
        m_direction = Direction::UP;
    Cycle();
}
void Game::Down()
{
    if (m_direction != Direction::UP)
        m_direction = Direction::DOWN;
    Cycle();
}
void Game::Left()
{
    if (m_direction != Direction::RIGHT)
        m_direction = Direction::LEFT;
    Cycle();
}
void Game::Right()
{
    if (m_direction != Direction::LEFT)
        m_direction = Direction::RIGHT;
    Cycle();
}
