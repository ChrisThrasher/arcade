#include "Scramble.h"

#include <random>

static constexpr std::array g_moves
    = { "U", "U'", "U2", "F", "F'", "F2", "L", "L'", "L2", "R", "R'", "R2", "B", "B'", "B2", "D", "D'", "D2" };

auto GenerateScramble() -> Scramble
{
    static std::random_device s_rd;
    static std::mt19937 s_rng(s_rd());
    static std::uniform_int_distribution<size_t> s_dist(0, g_moves.size() - 1);

    auto scramble = Scramble {};
    scramble[0] = g_moves.at(s_dist(s_rng));
    for (size_t i = 1; i < scramble.size(); ++i) {
        auto move = g_moves.at(s_dist(s_rng));
        while (move[0] == scramble[i - 1][0])
            move = g_moves.at(s_dist(s_rng));
        scramble[i] = move;
    }

    return scramble;
}
