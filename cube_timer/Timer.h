#pragma once

#include <chrono>

class Timer {
    std::chrono::time_point<std::chrono::system_clock> m_start {};
    std::chrono::nanoseconds m_duration {};
    bool m_running { false };

public:
    void Start();
    void Stop();
    void StartStop();
    void Reset();
    auto Query() -> std::chrono::nanoseconds;
};
