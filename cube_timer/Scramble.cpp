#include "Scramble.h"

#include <random>

auto GenerateMove() -> std::string
{
    constexpr std::array moves
        = { "U", "U'", "U2", "F", "F'", "F2", "L", "L'", "L2", "R", "R'", "R2", "B", "B'", "B2", "D", "D'", "D2" };

    static std::random_device s_rd;
    static std::mt19937 s_rng(s_rd());
    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);

    return moves[s_dist(s_rng)];
}

auto GenerateScramble() -> Scramble
{

    // This is a bit ugly
    auto scramble = Scramble {};
    scramble[0] = GenerateMove();
    scramble[1] = GenerateMove();
    while (scramble[1][0] == scramble[0][0])
        scramble[1] = GenerateMove();
    for (size_t i = 2; i < scramble.size(); ++i) {
        scramble[i] = GenerateMove();
        while (scramble[i][0] == scramble[i - 1][0] || scramble[i][0] == scramble[i - 2][0])
            scramble[i] = GenerateMove();
    }

    return scramble;
}
