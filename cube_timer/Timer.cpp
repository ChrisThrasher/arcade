#include "Timer.h"

void Timer::Update()
{
    auto now = std::chrono::system_clock::now();
    m_duration += now - m_start;
    m_start = now;
}

void Timer::Start()
{
    m_start = std::chrono::system_clock::now();
    m_running = true;
}

void Timer::Stop()
{
    Update();
    m_running = false;
}

void Timer::StartStop()
{
    if (m_running)
        Stop();
    else
        Start();
}

void Timer::Reset()
{
    m_start = std::chrono::system_clock::now();
    m_duration = std::chrono::nanoseconds(0);
}

auto Timer::Query() -> std::chrono::nanoseconds
{
    if (m_running)
        Update();

    return m_duration;
}
