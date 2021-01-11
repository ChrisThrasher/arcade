#include "Board.h"

void Merge(int& dest, int& src, int& score)
{
    if (dest == src)
        score += dest + src;
    dest += src;
    src = 0;
}

void ProcessTileset(int& tile1, int& tile2, int& tile3, int& tile4, int& score)
{
    std::array<std::reference_wrapper<int>, 4> tileset = {
        std::ref(tile1), std::ref(tile2), std::ref(tile3), std::ref(tile4)};

    // Sift down
    for (size_t i = 1; i < tileset.size(); ++i)
        for (auto j = i; j > 0 && tileset[j - 1] == 0; --j)
            Merge(tileset[j - 1], tileset[j], score);

    // Merge identical values
    for (size_t i = 1; i < tileset.size(); ++i)
        if (tileset[i - 1] == tileset[i])
            Merge(tileset[i - 1], tileset[i], score);

    // Sift one more time
    for (size_t i = 1; i < tileset.size(); ++i)
        for (auto j = i; j > 0 && tileset[j - 1] == 0; --j)
            Merge(tileset[j - 1], tileset[j], score);
}

Board::Board() { Reset(); }

void Board::Reset()
{
    m_score = 0;
    m_board = {};
    AddNewTile();
    AddNewTile();
}

void Board::Move(const Direction direction)
{
    const auto previous_board = m_board;

    switch (direction)
    {
    case Direction::UP:
        for (size_t column = 0; column < 4; ++column)
            ProcessTileset(m_board[0][column], m_board[1][column], m_board[2][column], m_board[3][column], m_score);
        break;
    case Direction::DOWN:
        for (size_t column = 0; column < 4; ++column)
            ProcessTileset(m_board[3][column], m_board[2][column], m_board[1][column], m_board[0][column], m_score);
        break;
    case Direction::LEFT:
        for (size_t row = 0; row < 4; ++row)
            ProcessTileset(m_board[row][0], m_board[row][1], m_board[row][2], m_board[row][3], m_score);
        break;
    case Direction::RIGHT:
        for (size_t row = 0; row < 4; ++row)
            ProcessTileset(m_board[row][3], m_board[row][2], m_board[row][1], m_board[row][0], m_score);
        break;
    }

    if (previous_board != m_board)
        AddNewTile();
}

void Board::AddNewTile()
{
    while (not IsFull())
    {
        auto& tile = m_board[m_location_distribution(m_rng)][m_location_distribution(m_rng)];
        if (tile == 0)
        {
            tile = m_value_distribution(m_rng) ? 4 : 2;
            return;
        }
    }
}

bool Board::IsFull() const
{
    for (const auto& row : m_board)
        for (const auto& tile : row)
            if (tile == 0)
                return false;
    return true;
}

auto Board::GameState() const -> Board::State
{
    for (const auto& row : m_board)
        for (const auto& tile : row)
            if (tile >= 2048)
                return State::SUCCESS;

    auto board = m_board;
    auto score = m_score;
    auto board_changed = false;
    for (size_t column = 0; column < 4; ++column)
    {
        ProcessTileset(board[0][column], board[1][column], board[2][column], board[3][column], score);
        if (board != m_board)
            board_changed = true;
    }
    for (size_t column = 0; column < 4; ++column)
    {
        ProcessTileset(board[3][column], board[2][column], board[1][column], board[0][column], score);
        if (board != m_board)
            board_changed = true;
    }
    for (size_t row = 0; row < 4; ++row)
    {
        ProcessTileset(board[row][0], board[row][1], board[row][2], board[row][3], score);
        if (board != m_board)
            board_changed = true;
    }
    for (size_t row = 0; row < 4; ++row)
    {
        ProcessTileset(board[row][3], board[row][2], board[row][1], board[row][0], score);
        if (board != m_board)
            board_changed = true;
    }

    if (not board_changed)
        return State::FAILURE;

    return State::IN_PROGRESS;
}
