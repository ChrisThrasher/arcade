#include "ConnectFour.h"

#include <vector>

bool FourInARow(const std::vector<Tile>& line)
{
    int consecutive_matches = 1;
    for (size_t i = 1; i < line.size(); ++i)
    {
        if (line[i] == line[i - 1] and line[i] != Tile::EMPTY)
            ++consecutive_matches;
        else
            consecutive_matches = 1;

        if (consecutive_matches == 4)
            return true;
    }

    return false;
}

bool ConnectFour::IsRunning() const
{
    // Check columns
    for (size_t col = 0; col < Cols(); ++col)
    {
        std::vector<Tile> tiles;
        for (size_t row = 0; row < Rows(); ++row)
            tiles.push_back(m_board[col][row]);
        if (FourInARow(tiles))
            return false;
    }

    // Check rows
    for (size_t row = 0; row < Rows(); ++row)
    {
        std::vector<Tile> tiles;
        for (size_t col = 0; col < Cols(); ++col)
            tiles.push_back(m_board[col][row]);
        if (FourInARow(tiles))
            return false;
    }

    // Check '/' diagonals
    for (size_t diag = 0; diag < Rows(); ++diag) // Along left edge
    {
        std::vector<Tile> tiles;
        for (size_t col = 0; diag + col < Rows(); ++col)
            tiles.push_back(m_board[col][diag + col]);
        if (FourInARow(tiles))
            return false;
    }
    for (size_t diag = 1; diag < Cols(); ++diag) // Along bottom edge
    {
        std::vector<Tile> tiles;
        for (size_t row = 0; diag + row < Cols(); ++row)
            tiles.push_back(m_board[diag + row][row]);
        if (FourInARow(tiles))
            return false;
    }

    // Check '\' diagonals
    for (size_t diag = 0; diag < Rows(); ++diag) // Along right edge
    {
        std::vector<Tile> tiles;
        for (size_t col = 0; diag + col < Rows(); ++col)
            tiles.push_back(m_board[Cols() - col - 1][diag + col]);
        if (FourInARow(tiles))
            return false;
    }
    for (size_t diag = 1; diag < Cols(); ++diag) // Along bottom edge
    {
        std::vector<Tile> tiles;
        for (size_t row = 0; diag + row < Cols(); ++row)
            tiles.push_back(m_board[Cols() - diag - row - 1][row]);
        if (FourInARow(tiles))
            return false;
    }

    return true;
}

void ConnectFour::Add(size_t location)
{
    for (auto& tile : m_board[location])
    {
        if (tile == Tile::EMPTY)
        {
            tile = m_active_tile;
            m_active_tile = (m_active_tile == Tile::RED) ? Tile::YEL : Tile::RED;
            break;
        }
    }

    m_running = IsRunning();
}
