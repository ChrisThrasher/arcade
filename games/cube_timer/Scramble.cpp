#include "Scramble.h"

#include <array>
#include <optional>
#include <random>

static std::random_device g_rd;
static std::mt19937 g_rng(g_rd());

auto Generate2x2Move(const std::optional<std::string>& prev1 = std::nullopt) -> std::string
{
    constexpr std::array moves = { "U", "U'", "U2", "F", "F'", "F2", "R", "R'", "R2" };

    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);

    std::string move = moves[s_dist(g_rng)];
    while (move[0] == prev1.value_or("")[0])
        move = moves[s_dist(g_rng)];
    return move;
}

auto Generate2x2Scramble()
{
    constexpr auto length = 9;

    auto scramble = Scramble {};
    scramble.push_back(Generate2x2Move());
    for (size_t i = 1; i < length; ++i)
        scramble.push_back(Generate2x2Move(scramble[i - 1]));

    return scramble;
}

auto Generate3x3Move(const std::optional<std::string>& prev1 = std::nullopt,
                     const std::optional<std::string>& prev2 = std::nullopt) -> std::string
{
    constexpr std::array moves
        = { "U", "U'", "U2", "F", "F'", "F2", "L", "L'", "L2", "R", "R'", "R2", "B", "B'", "B2", "D", "D'", "D2" };

    static std::uniform_int_distribution<size_t> s_dist(0, moves.size() - 1);

    std::string move = moves[s_dist(g_rng)];
    while (move[0] == prev1.value_or("")[0] || move[0] == prev2.value_or("")[0])
        move = moves[s_dist(g_rng)];
    return move;
}

auto Generate3x3Scramble()
{
    constexpr auto length = 18;

    auto scramble = Scramble {};
    scramble.push_back(Generate3x3Move());
    scramble.push_back(Generate3x3Move(scramble[0]));
    for (size_t i = 2; i < length; ++i)
        scramble.push_back(Generate3x3Move(scramble[i - 1], scramble[i - 2]));

    return scramble;
}

auto GenerateScramble(const Puzzle puzzle) -> Scramble
{
    switch (puzzle) {
    case Puzzle::Cube2:
        return Generate2x2Scramble();
    case Puzzle::Cube3:
        return Generate3x3Scramble();
    case Puzzle::Cube4:
        // TODO Implement 4x4 scrambling
        return {};
    case Puzzle::Cube5:
        // TODO Implement 5x5 scrambling
        return {};
    }

    return {};
}
