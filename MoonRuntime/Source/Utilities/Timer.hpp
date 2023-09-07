#pragma once

#include <chrono>
#include <string>

class Timer
{
public:
    Timer(const std::string& name = "Timer");
    virtual ~Timer() = default;

    // Returns the amount of time that has passed since last calling GetTime() or GetDelta()
    float GetDelta();

protected:
    std::string m_Name;
    std::chrono::steady_clock::time_point m_Start;
    std::chrono::steady_clock::time_point m_Last;
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

    // Returns the amount of time since the construction of the timer
    float GetTime();
};
