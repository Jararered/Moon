#pragma once

#include <vector>

#include "Camera.hpp"
#include "render/Mesh.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Update(float dt);
    
    Camera& CreateCamera();
    Mesh& CreateTestMesh();

private:
    std::vector<Camera> m_Cameras;
    std::vector<Mesh> m_Meshes;
};