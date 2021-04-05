#include "Scramble.h"

#include <array>
#include <cctype>
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

static auto Generate4x4Move() -> std::string
{
    constexpr std::array moves
        = { "U",  "U'",  "U2",  "F",  "F'",  "F2",  "L",  "L'",  "L2",  "R",   "R'",  "R2", "B",   "B'",
            "B2", "D",   "D'",  "D2", "u",   "u'",  "u2", "f",   "f'",  "f2",  "l",   "l'", "l2",  "r",
            "r'", "r2",  "b",   "b'", "b2",  "d",   "d'", "d2",  "Uw",  "Uw'", "Uw2", "Fw", "Fw'", "Fw2",
            "Lw", "Lw'", "Lw2", "Rw", "Rw'", "Rw2", "Bw", "Bw'", "Bw2", "Dw",  "Dw'", "Dw2" };

    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);
    static std::string prev1;
    static std::string prev2;

    std::string move = moves[s_dist(g_rng)];
    while (std::tolower(move[0]) == std::tolower(prev1[0]) || std::tolower(move[0]) == std::tolower(prev2[0]))
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
        return GenerateScramble(21, Generate3x3Move);
    case Puzzle::Cube4:
        return GenerateScramble(28, Generate4x4Move);
    case Puzzle::Cube5:
        return GenerateScramble(35, Generate4x4Move);
    case Puzzle::Cube6:
        return {};
    case Puzzle::Cube7:
        return {};
    }

    return {};
}
