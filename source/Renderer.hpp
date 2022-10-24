#pragma once

#include <vector>

#include "Camera.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Update();
    Camera& CreateCamera();

private:
    std::vector<Camera> m_Cameras;
};