#include "Timer.h"

auto Now() { return std::chrono::system_clock::now(); }

void Timer::Start()
{
    m_start = Now();
    m_running = true;
}

void Timer::Stop()
{
    auto now = Now();
    m_duration += now - m_start;
    m_start = now;
    m_running = false;
}

void Timer::Toggle()
{
    if (m_running)
        Stop();
    else
        Start();
}

void Timer::Reset()
{
    m_start = Now();
    m_duration = std::chrono::nanoseconds(0);
}

void Timer::Clear()
{
    Stop();
    Reset();
}

void Timer::Restart()
{
    Clear();
    Start();
}

auto Timer::Query() const -> std::chrono::nanoseconds
{
    if (m_running)
        return Now() - m_start + m_duration;
    return m_duration;
}
