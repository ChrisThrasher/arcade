#pragma once

#include <string>
#include <vector>

enum class Puzzle { Cube2, Cube3, Cube4, Cube5 };
using Scramble = std::vector<std::string>;
auto GenerateScramble(Puzzle) -> Scramble;
