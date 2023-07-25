#pragma once

class Renderer;

enum GraphicsAPI
{
    OpenGL,
    Vulkan,
    Metal
};

class Window
{
public:
    Window() {};
    virtual ~Window() {};

    virtual void Update(float dt) = 0;
    virtual bool IsRunning() = 0;
    virtual Renderer& CreateRenderer() = 0;

protected:
    int m_Height = 1280;
    int m_Width = 1280;
};