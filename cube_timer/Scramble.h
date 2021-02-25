#pragma once

#include <array>
#include <string>

using Scramble = std::array<std::string, 18>;
auto GenerateScramble() -> Scramble;
