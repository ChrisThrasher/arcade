#include "Timer.h"

auto Now() { return std::chrono::system_clock::now(); }

void Timer::Update()
{
    auto now = Now();
    m_duration += now - m_start;
    m_start = now;
}

void Timer::Start()
{
    m_start = Now();
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
    m_start = Now();
    m_duration = std::chrono::nanoseconds(0);
}

auto Timer::Query() -> std::chrono::nanoseconds
{
    if (m_running)
        return Now() - m_start + m_duration;
    else
        return m_duration;
}
