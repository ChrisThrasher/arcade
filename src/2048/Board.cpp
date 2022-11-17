#include "Board.hpp"

static auto rng = std::mt19937(std::random_device()());

static void merge(int& dest, int& src, int& score)
{
    if (dest == src)
        score += dest + src;
    dest += src;
    src = 0;
}

static void process_tileset(int& tile1, int& tile2, int& tile3, int& tile4, int& score)
{
    std::array<std::reference_wrapper<int>, 4> tileset
        = { std::ref(tile1), std::ref(tile2), std::ref(tile3), std::ref(tile4) };

    // Sift down
    for (size_t i = 1; i < tileset.size(); ++i)
        for (auto j = i; j > 0 && tileset[j - 1] == 0; --j)
            merge(tileset[j - 1], tileset[j], score);

    // Merge identical values
    for (size_t i = 1; i < tileset.size(); ++i)
        if (tileset[i - 1] == tileset[i])
            merge(tileset[i - 1], tileset[i], score);

    // Sift one more time
    for (size_t i = 1; i < tileset.size(); ++i)
        for (auto j = i; j > 0 && tileset[j - 1] == 0; --j)
            merge(tileset[j - 1], tileset[j], score);
}

Board::Board() { reset(); }

void Board::reset()
{
    m_score = 0;
    m_board = {};
    add_new_tile();
    add_new_tile();
}

void Board::move(const Direction direction)
{
    const auto previous_board = m_board;

    switch (direction) {
    case Direction::UP:
        for (size_t column = 0; column < 4; ++column)
            process_tileset(m_board[0][column], m_board[1][column], m_board[2][column], m_board[3][column], m_score);
        break;
    case Direction::DOWN:
        for (size_t column = 0; column < 4; ++column)
            process_tileset(m_board[3][column], m_board[2][column], m_board[1][column], m_board[0][column], m_score);
        break;
    case Direction::LEFT:
        for (size_t row = 0; row < 4; ++row)
            process_tileset(m_board[row][0], m_board[row][1], m_board[row][2], m_board[row][3], m_score);
        break;
    case Direction::RIGHT:
        for (size_t row = 0; row < 4; ++row)
            process_tileset(m_board[row][3], m_board[row][2], m_board[row][1], m_board[row][0], m_score);
        break;
    }

    if (previous_board != m_board)
        add_new_tile();
}

void Board::add_new_tile()
{
    while (not is_full()) {
        auto& tile = m_board[m_location_distribution(rng)][m_location_distribution(rng)];
        if (tile == 0) {
            tile = m_value_distribution(rng) ? 4 : 2;
            return;
        }
    }
}

bool Board::is_full() const
{
    for (const auto& row : m_board)
        for (const auto& tile : row)
            if (tile == 0)
                return false;
    return true;
}

auto Board::game_state() const -> Board::State
{
    for (const auto& row : m_board)
        for (const auto& tile : row)
            if (tile >= 2048)
                return State::SUCCESS;

    auto board = m_board;
    auto score = m_score;
    for (size_t column = 0; column < 4; ++column) {
        process_tileset(board[0][column], board[1][column], board[2][column], board[3][column], score);
        if (board != m_board)
            return State::IN_PROGRESS;
    }
    for (size_t column = 0; column < 4; ++column) {
        process_tileset(board[3][column], board[2][column], board[1][column], board[0][column], score);
        if (board != m_board)
            return State::IN_PROGRESS;
    }
    for (size_t row = 0; row < 4; ++row) {
        process_tileset(board[row][0], board[row][1], board[row][2], board[row][3], score);
        if (board != m_board)
            return State::IN_PROGRESS;
    }
    for (size_t row = 0; row < 4; ++row) {
        process_tileset(board[row][3], board[row][2], board[row][1], board[row][0], score);
        if (board != m_board)
            return State::IN_PROGRESS;
    }

    return State::FAILURE;
}
