#pragma once

#include <chrono>

class Timer {
    std::chrono::time_point<std::chrono::system_clock> m_start {};
    std::chrono::nanoseconds m_duration {};
    bool m_running { false };

public:
    void start();
    void stop();
    void toggle();
    void reset();
    void clear();
    void restart();

    [[nodiscard]] auto query() const -> std::chrono::nanoseconds;
    [[nodiscard]] auto running() const { return m_running; }
};
