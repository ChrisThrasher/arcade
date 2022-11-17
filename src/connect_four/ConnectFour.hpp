#pragma once

#include <array>
#include <cstddef>

enum class Tile { EMPTY, RED, YEL };

class ConnectFour {
    std::array<std::array<Tile, 6>, 7> m_board; // column-wise indexing
    Tile m_active_tile { Tile::RED };
    bool m_running { true };

    [[nodiscard]] bool is_running() const;
    [[nodiscard]] auto cols() const { return m_board.size(); }
    [[nodiscard]] auto rows() const { return m_board[0].size(); }

public:
    void add(size_t location);
    [[nodiscard]] auto board() const { return m_board; }
    [[nodiscard]] auto running() const { return m_running; }
    [[nodiscard]] auto active_tile() const { return m_active_tile; }
};
