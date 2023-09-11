#pragma once

#include <chrono>
#include <string>

class Timer
{
public:
    Timer() = default;
    Timer(const Timer&) = default;
    Timer(Timer&&) = default;
    Timer& operator=(const Timer&) = default;
    Timer& operator=(Timer&&) = default;
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
    ScopedTimer(const ScopedTimer&) = default;
    ScopedTimer(ScopedTimer&&) = default;
    ScopedTimer& operator=(const ScopedTimer&) = default;
    ScopedTimer& operator=(ScopedTimer&&) = default;

public:
    ScopedTimer(const std::string& name = "Timer");
    ~ScopedTimer();
};

class ManualTimer final : protected Timer
{
public:
    ManualTimer() = default;
    ManualTimer(const ManualTimer&) = default;
    ManualTimer(ManualTimer&&) = default;
    ManualTimer& operator=(const ManualTimer&) = default;
    ManualTimer& operator=(ManualTimer&&) = default;
    ~ManualTimer() = default;

public:
    ManualTimer(const std::string& name = "Timer");

    void Start();
    void Stop();

    // Returns the amount of time since the construction of the timer
    [[nodiscard]] float GetTime();
};
