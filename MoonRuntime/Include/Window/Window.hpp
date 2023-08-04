#pragma once

#include "Layer.hpp"
#include "Renderer.hpp"

#include <vector>

struct WindowSpecification
{
    enum GraphicsAPI
    {
        OpenGL,
        Vulkan,
        Metal
    };

    GraphicsAPI API = GraphicsAPI::OpenGL;
    float Width = 1280;
    float Height = 720;
    bool VSync = true;
    bool EnableImgui = false;
};

class Window
{
public:
    Window(const WindowSpecification& spec) : m_WindowSpecification(spec){};
    virtual ~Window(){};

    virtual void Update(float dt) = 0;
    virtual bool IsRunning() = 0;
    virtual Renderer* CreateRenderer() = 0;

    WindowSpecification m_WindowSpecification;

protected:
    std::vector<Layer> m_LayerVector;

public:
    void AddLayer(const Layer& layer) { m_LayerVector.emplace_back(layer); }
};