#pragma once

#include "Renderer/Camera/Camera.hpp"
#include "Renderer/Structures/Mesh.hpp"

#include <vector>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Update(float dt);

    Camera& Create2DCamera();
    Camera& Create3DCamera();

    void AddMesh(Mesh* mesh);

private:
    std::vector<Camera> m_Cameras;
    std::vector<Mesh*> m_Meshes;
};