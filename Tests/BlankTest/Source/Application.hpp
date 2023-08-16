#pragma once

#include <Moon.hpp>

class Application : public Engine
{
public:
    void Start()
    {
        while (p_Window->IsRunning())
        {
            auto frameStartTime = std::chrono::high_resolution_clock::now();

            Update();

            // p_CameraSystem->Update(m_DeltaFrameTime);
            // p_VerletSystem->Update(m_DeltaFrameTime);
            // p_RenderSystem->Update(m_DeltaFrameTime);

            auto frameEndTime = std::chrono::high_resolution_clock::now();
            m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
        }
    }
};