#pragma once

#include "Mesh.hpp"
#include "Collider.hpp"

class Entity
{
public:
    virtual void Initialize(float dt) {}
    virtual void Update(float dt) {}
    virtual void Finalize(float dt) {}

    void Attach(Mesh* mesh) { p_Mesh = mesh; }
    void Attach(Collider* collider) { p_Collision = collider; }

    Mesh* GetMesh() { return p_Mesh; }
    Collider* GetCollision() { return p_Collision; }

protected:
    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

protected:
    Mesh* p_Mesh = nullptr;
    Collider* p_Collision = nullptr;
};