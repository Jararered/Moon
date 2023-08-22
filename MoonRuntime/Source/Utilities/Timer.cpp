#include "Timer.hpp"

#include <iostream>

Timer::Timer(const std::string& name) : m_Name(name)
{
}

ScopedTimer::ScopedTimer(const std::string& name) : Timer(name)
{
    m_Start = std::chrono::high_resolution_clock::now();
}

ScopedTimer::~ScopedTimer()
{
    m_Stop = std::chrono::high_resolution_clock::now();
    std::cout << m_Name << " took: " << std::chrono::duration<float, std::chrono::seconds::period>(m_Stop - m_Start).count() << " seconds.\n";
}

ManualTimer::ManualTimer(const std::string& name) : Timer(name)
{
}

void ManualTimer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

void ManualTimer::Stop()
{
    m_Stop = std::chrono::high_resolution_clock::now();
    std::cout << m_Name << " took: " << std::chrono::duration<float, std::chrono::seconds::period>(m_Stop - m_Start).count() << " seconds.\n";
}

float ManualTimer::GetTime()
{
    return std::chrono::duration<float, std::chrono::seconds::period>(m_Stop - m_Start).count();
}