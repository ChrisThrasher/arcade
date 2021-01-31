#pragma once

#include <array>
#include <cstddef>

enum class Tile
{
    EMPTY,
    RED,
    YEL
};

class ConnectFour
{
    std::array<std::array<Tile, 6>, 7> m_board{}; // column-wise indexing
    Tile m_active_tile{Tile::RED};
    bool m_running{true};

    bool IsRunning() const;
    auto Cols() const { return m_board.size(); }
    auto Rows() const { return m_board[0].size(); }

public:
    void Add(size_t);
    auto Board() const { return m_board; }
    auto Running() const { return m_running; }
    auto ActiveTile() const { return m_active_tile; }
};
