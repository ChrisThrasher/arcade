#include "Timer.hpp"

static auto now() { return std::chrono::system_clock::now(); }

void Timer::start()
{
    m_start = now();
    m_running = true;
}

void Timer::stop()
{
    auto current_time = now();
    m_duration += current_time - m_start;
    m_start = current_time;
    m_running = false;
}

void Timer::toggle()
{
    if (m_running)
        stop();
    else
        start();
}

void Timer::reset()
{
    m_start = now();
    m_duration = std::chrono::nanoseconds(0);
}

void Timer::clear()
{
    stop();
    reset();
}

void Timer::restart()
{
    clear();
    start();
}

auto Timer::query() const -> std::chrono::nanoseconds
{
    if (m_running)
        return now() - m_start + m_duration;
    return m_duration;
}
