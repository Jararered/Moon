#include "Timer.hpp"

using namespace Moon;

Timer::Timer(std::string_view name) : m_Name(name.data())
{
    m_Start = std::chrono::high_resolution_clock::now();
}

float Timer::GetDelta()
{
    auto delta = std::chrono::duration<float, std::chrono::milliseconds::period>(std::chrono::high_resolution_clock::now() - m_Last).count();
    m_Last = std::chrono::high_resolution_clock::now();
    return delta;
}

ScopedTimer::ScopedTimer(std::string_view name) : Timer(name.data())
{
}

ScopedTimer::~ScopedTimer()
{
    m_Stop = std::chrono::high_resolution_clock::now();
    // std::println("{} took: {:5.5f} ms.", m_Name, std::chrono::duration<float, std::chrono::milliseconds::period>(m_Stop - m_Start).count());
}

ManualTimer::ManualTimer(std::string_view name) : Timer(name.data())
{
}

void ManualTimer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

void ManualTimer::Stop()
{
    m_Stop = std::chrono::high_resolution_clock::now();
    // std::println("{} took: {:5.5f} ms.", m_Name, std::chrono::duration<float, std::chrono::milliseconds::period>(m_Stop - m_Start).count());
}

float ManualTimer::GetTime()
{
    return std::chrono::duration<float, std::chrono::milliseconds::period>(m_Stop - m_Start).count();
}
