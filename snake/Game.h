#pragma once

#include <array>
#include <deque>
#include <random>

class Game
{
    enum class Direction
    {
        NONE = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    void AddFruit();

public:
    enum class Tile
    {
        EMPTY = 0,
        SNAKE,
        FRUIT
    };

    Game();

    void Cycle();
    void Up();
    void Down();
    void Left();
    void Right();

    bool Running() const { return m_running; }
    auto Board() const { return m_board; }
    auto Score() const { return m_score; }

private:
    static constexpr size_t m_size{20};
    std::array<std::array<Tile, m_size>, m_size> m_board{};
    std::deque<std::reference_wrapper<Tile>> m_snake{};
    std::pair<size_t, size_t> m_head{1, 3};
    Direction m_direction{Direction::NONE};
    bool m_running{true};
    int m_score{0};

    std::random_device m_rd{};
    std::mt19937 m_rng{m_rd()};
    std::uniform_int_distribution<size_t> m_distribution{0, m_size - 1};
};
