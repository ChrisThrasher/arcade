#include "ConnectFour.h"

#include <vector>

bool four_in_a_row(const std::vector<Tile>& line)
{
    int consecutive_matches = 1;
    for (size_t i = 1; i < line.size(); ++i) {
        if (line[i] == line[i - 1] and line[i] != Tile::EMPTY)
            ++consecutive_matches;
        else
            consecutive_matches = 1;

        if (consecutive_matches == 4)
            return true;
    }

    return false;
}

bool ConnectFour::is_running() const
{
    // Check columns
    for (size_t col = 0; col < cols(); ++col) {
        std::vector<Tile> tiles;
        for (size_t row = 0; row < rows(); ++row)
            tiles.push_back(m_board[col][row]);
        if (four_in_a_row(tiles))
            return false;
    }

    // Check rows
    for (size_t row = 0; row < rows(); ++row) {
        std::vector<Tile> tiles;
        for (size_t col = 0; col < cols(); ++col)
            tiles.push_back(m_board[col][row]);
        if (four_in_a_row(tiles))
            return false;
    }

    // Check '/' diagonals
    for (size_t diag = 0; diag < rows(); ++diag) // Along left edge
    {
        std::vector<Tile> tiles;
        for (size_t col = 0; diag + col < rows(); ++col)
            tiles.push_back(m_board[col][diag + col]);
        if (four_in_a_row(tiles))
            return false;
    }
    for (size_t diag = 1; diag < cols(); ++diag) // Along bottom edge
    {
        std::vector<Tile> tiles;
        for (size_t row = 0; diag + row < cols(); ++row)
            tiles.push_back(m_board[diag + row][row]);
        if (four_in_a_row(tiles))
            return false;
    }

    // Check '\' diagonals
    for (size_t diag = 0; diag < rows(); ++diag) // Along right edge
    {
        std::vector<Tile> tiles;
        for (size_t col = 0; diag + col < rows(); ++col)
            tiles.push_back(m_board[cols() - col - 1][diag + col]);
        if (four_in_a_row(tiles))
            return false;
    }
    for (size_t diag = 1; diag < cols(); ++diag) // Along bottom edge
    {
        std::vector<Tile> tiles;
        for (size_t row = 0; diag + row < cols(); ++row)
            tiles.push_back(m_board[cols() - diag - row - 1][row]);
        if (four_in_a_row(tiles))
            return false;
    }

    return true;
}

void ConnectFour::add(size_t location)
{
    for (auto& tile : m_board[location]) {
        if (tile == Tile::EMPTY) {
            tile = m_active_tile;
            m_active_tile = (m_active_tile == Tile::RED) ? Tile::YEL : Tile::RED;
            break;
        }
    }

    m_running = is_running();
}
