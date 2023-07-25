#pragma once

#include "Camera.hpp"
#include "Mesh.hpp"

#include <vector>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Update(float dt);

    void AddCamera(Camera* camera);
    void AddMesh(Mesh* mesh);

private:
    std::vector<Camera*> m_Cameras;
    std::vector<Mesh*> m_Meshes;
};