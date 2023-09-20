#pragma once

#include <chrono>
#include <string>

class Timer
{
public:
    Timer() = default;
    virtual ~Timer() = default;

    Timer(const std::string& name = "Timer");

    // Returns the amount of time that has passed since last calling GetTime() or GetDelta()
    [[nodiscard]] float GetDelta();

protected:
    std::string m_Name;
    std::chrono::steady_clock::time_point m_Start;
    std::chrono::steady_clock::time_point m_Last;
    std::chrono::steady_clock::time_point m_Stop;
};

class ScopedTimer final : protected Timer
{
public:
    ScopedTimer() = default;
    ~ScopedTimer() override;

    ScopedTimer(const std::string& name = "Timer");
};

class ManualTimer final : protected Timer
{
public:
    ManualTimer() = default;
    ~ManualTimer() override = default;

    ManualTimer(const std::string& name = "Timer");

    void Start();
    void Stop();

    // Returns the amount of time since the construction of the timer
    [[nodiscard]] float GetTime();
};
