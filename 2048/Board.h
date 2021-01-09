#pragma once

#include <array>
#include <functional>
#include <random>

void Merge(int& dest, int& src);
void ProcessTileset(int& tile1, int& tile2, int& tile3, int& tile4, int& score);

class Board
{
    std::array<std::array<int, 4>, 4> m_board{};
    std::random_device m_rd{};
    std::mt19937 m_rng{m_rd()};
    std::uniform_int_distribution<size_t> m_location_distribution{0, 3};
    std::bernoulli_distribution m_value_distribution{0.1};
    int m_score{0};

    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    void Move(const Direction);
    void AddNewTile();
    bool IsFull() const;

public:
    Board();

    enum class State
    {
        IN_PROGRESS,
        SUCCESS,
        FAILURE
    };

    void Reset();
    auto GameState() const -> State;
    auto Score() const { return m_score; }
    auto Data() const { return m_board; }

    void Up() { Move(Direction::UP); }
    void Down() { Move(Direction::DOWN); }
    void Left() { Move(Direction::LEFT); }
    void Right() { Move(Direction::RIGHT); }
};
