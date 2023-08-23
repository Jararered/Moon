#pragma once

#include <chrono>
#include <string>

class Timer
{
public:
    Timer(const std::string& name = "Timer");
    virtual ~Timer() = default;

protected:
    std::string m_Name;
    std::chrono::steady_clock::time_point m_Start;
    std::chrono::steady_clock::time_point m_Stop;
};

class ScopedTimer : protected Timer
{
public:
    ScopedTimer(const std::string& name = "Timer");
    ~ScopedTimer();
};

class ManualTimer : protected Timer
{
public:
    ManualTimer(const std::string& name = "Timer");
    ~ManualTimer() = default;

    void Start();
    void Stop();
    float GetTime();
};