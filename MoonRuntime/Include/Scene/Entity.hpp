#pragma once

#include "Collider.hpp"
#include "Mesh.hpp"

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void Update(float dt) {}

    virtual void UpdateDynamics(float dt)
    {
        // Updates the mesh's location with the entity's position
        glm::mat4 translation = glm::mat4(1.0f);
        translation = glm::translate(translation, m_Position);
        p_Mesh->SetTranslationMatrix(translation);
    }

protected:
    MeshBase* p_Mesh = nullptr;
    Collider* p_Collider = nullptr;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};

public:
    glm::vec3 GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

    MeshBase* GetMesh() const { return p_Mesh; }
    void SetMesh(MeshBase* mesh) { p_Mesh = mesh; }

    Collider* GetCollider() const { return p_Collider; }
    void SetPCollider(Collider* collider) { p_Collider = collider; }
};