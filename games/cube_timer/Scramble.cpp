#include "Scramble.h"

#include <array>
#include <functional>
#include <random>

static std::random_device g_rd;
static std::mt19937 g_rng(g_rd());

static auto Generate2x2Move() -> std::string
{
    constexpr std::array moves = { "U", "U'", "U2", "F", "F'", "F2", "R", "R'", "R2" };

    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);
    static std::string prev;

    std::string move = moves[s_dist(g_rng)];
    while (move[0] == prev[0])
        move = moves[s_dist(g_rng)];

    prev = move;
    return move;
}

static auto Generate3x3Move() -> std::string
{
    constexpr std::array moves
        = { "U", "U'", "U2", "F", "F'", "F2", "L", "L'", "L2", "R", "R'", "R2", "B", "B'", "B2", "D", "D'", "D2" };

    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);
    static std::string prev1;
    static std::string prev2;

    std::string move = moves[s_dist(g_rng)];
    while (move[0] == prev1[0] || move[0] == prev2[0])
        move = moves[s_dist(g_rng)];

    prev2 = prev1;
    prev1 = move;
    return move;
}

static auto GenerateScramble(const size_t length, const std::function<std::string()>& generator)
{
    auto scramble = Scramble {};
    for (size_t i = 0; i < length; ++i)
        scramble.push_back(generator());
    return scramble;
}

auto GenerateScramble(const Puzzle puzzle) -> Scramble
{
    switch (puzzle) {
    case Puzzle::Cube2:
        return GenerateScramble(9, Generate2x2Move);
    case Puzzle::Cube3:
        return GenerateScramble(18, Generate3x3Move);
    case Puzzle::Cube4:
        // TODO Implement 4x4 scrambling
        return {};
    case Puzzle::Cube5:
        // TODO Implement 5x5 scrambling
        return {};
    }

    return {};
}
