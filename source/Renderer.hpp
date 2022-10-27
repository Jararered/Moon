#pragma once

#include <vector>

#include "render/camera/Camera.hpp"
#include "render/Mesh.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Update(float dt);
    
    Camera& Create2DCamera();
    Camera& Create3DCamera();
    Mesh& CreateTestMesh();

private:
    std::vector<Camera> m_Cameras;
    std::vector<Mesh> m_Meshes;
};