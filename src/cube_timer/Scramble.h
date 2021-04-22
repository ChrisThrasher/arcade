#pragma once

#include <string>
#include <vector>

enum class Puzzle { Cube2, Cube3, Cube4, Cube5, Cube6, Cube7 };
using Scramble = std::vector<std::string>;
auto generate_scramble(Puzzle) -> Scramble;
