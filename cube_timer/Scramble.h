#pragma once

#include <array>
#include <string>

using Scramble = std::array<std::string, 20>;
auto GenerateScramble() -> Scramble;
