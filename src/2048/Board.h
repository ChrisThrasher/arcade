#pragma once

#include <array>
#include <functional>
#include <random>

class Board {
    std::array<std::array<int, 4>, 4> m_board {};
    std::random_device m_rd {};
    std::mt19937 m_rng { m_rd() };
    std::uniform_int_distribution<size_t> m_location_distribution { 0, 3 };
    std::bernoulli_distribution m_value_distribution { 0.1 };
    int m_score { 0 };

    enum class Direction { UP, DOWN, LEFT, RIGHT };

    void move(const Direction);
    void add_new_tile();
    bool is_full() const;

public:
    Board();

    enum class State { IN_PROGRESS, SUCCESS, FAILURE };

    void reset();
    auto game_state() const -> State;
    auto score() const { return m_score; }
    auto data() const { return m_board; }

    void up() { move(Direction::UP); }
    void down() { move(Direction::DOWN); }
    void left() { move(Direction::LEFT); }
    void right() { move(Direction::RIGHT); }
};
