#pragma once

#include "WindowSpecification.hpp"

namespace Moon
{

    class Window
    {
    public:
        Window(const WindowSpecification& spec) : m_WindowSpecification(spec){};
        virtual ~Window() = default;

        virtual void NewFrame() = 0;
        virtual void EndFrame() = 0;

        virtual bool IsRunning() = 0;

        WindowSpecification m_WindowSpecification;
    };

}