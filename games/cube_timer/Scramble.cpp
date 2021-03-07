#include "Scramble.h"

#include <array>
#include <optional>
#include <random>

auto GenerateMove(const std::optional<std::string> prev1 = std::nullopt,
                  const std::optional<std::string> prev2 = std::nullopt) -> std::string
{
    constexpr std::array moves
        = { "U", "U'", "U2", "F", "F'", "F2", "L", "L'", "L2", "R", "R'", "R2", "B", "B'", "B2", "D", "D'", "D2" };

    static std::random_device s_rd;
    static std::mt19937 s_rng(s_rd());
    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);

    std::string move = moves[s_dist(s_rng)];
    while (move[0] == prev1.value_or("")[0] || move[0] == prev2.value_or("")[0])
        move = moves[s_dist(s_rng)];
    return move;
}

auto GenerateScramble(const Puzzle puzzle) -> Scramble
{
    size_t length = 0;
    switch (puzzle) {
    case Puzzle::Cube2:
        length = 9;
        break;
    case Puzzle::Cube3:
        length = 18;
        break;
    case Puzzle::Cube4:
        // TODO Implement 4x4 scrambling
        return {};
    case Puzzle::Cube5:
        // TODO Implement 5x5 scrambling
        return {};
    }

    auto scramble = Scramble {};
    scramble.push_back(GenerateMove());
    scramble.push_back(GenerateMove(scramble[0]));
    for (size_t i = 2; i < length; ++i)
        scramble.push_back(GenerateMove(scramble[i - 1], scramble[i - 2]));

    return scramble;
}
