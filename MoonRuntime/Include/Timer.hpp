#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Timer
{
public:
    Timer(const std::string& name = "Timer") : m_Name(name) {}

protected:
    std::string m_Name;
    std::chrono::steady_clock::time_point m_Start;
    std::chrono::steady_clock::time_point m_Stop;
};

class ScopedTimer : protected Timer
{
public:
    ScopedTimer(const std::string& name = "Timer") : Timer(name) { m_Start = std::chrono::high_resolution_clock::now(); }
    ~ScopedTimer()
    {
        m_Stop = std::chrono::high_resolution_clock::now();
        std::cout << m_Name << " took: " << std::chrono::duration<float, std::chrono::seconds::period>(m_Stop - m_Start).count() << " seconds.\n";
    }
};

class ManualTimer : protected Timer
{
public:
    ManualTimer(const std::string& name = "Timer") : Timer(name) {}
    ~ManualTimer() {}

    void Start() { m_Start = std::chrono::high_resolution_clock::now(); }
    void Stop()
    {
        m_Stop = std::chrono::high_resolution_clock::now();
        std::cout << m_Name << " took: " << std::chrono::duration<float, std::chrono::seconds::period>(m_Stop - m_Start).count() << " seconds.\n";
    }
    float GetTime() { return std::chrono::duration<float, std::chrono::seconds::period>(m_Stop - m_Start).count(); }
};
