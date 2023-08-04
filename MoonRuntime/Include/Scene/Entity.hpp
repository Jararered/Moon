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
        const glm::vec3 last_update_move = m_Position - m_LastPosition;
        const glm::vec3 new_position = m_Position + last_update_move + (m_Acceleration - last_update_move * 40.0f) * (dt * dt);
        m_LastPosition = m_Position;
        m_Position = new_position;
        m_Acceleration = {0.0f, 0.0f, 0.0f};

        // Updates the mesh's location with the entity's m_Position
        glm::mat4 translation = glm::mat4(1.0f);
        translation = glm::translate(translation, m_Position);
        p_Mesh->SetTranslationMatrix(translation);
    }

protected:
    MeshBase* p_Mesh = nullptr;
    Collider* p_Collider = nullptr;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_LastPosition = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Acceleration = {0.0f, 0.0f, 0.0f};

public:
    void AddAcceleration(const glm::vec3& acceleration) { m_Acceleration += acceleration; }

    void SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        m_LastPosition = position;
    }

    void Stop() { m_LastPosition = m_Position; }

    void Slowdown(float ratio) { m_LastPosition = m_LastPosition + ratio * (m_Position - m_LastPosition); }

    float GetSpeed() const { return glm::length(m_Position - m_LastPosition); }

    glm::vec3 GetVelocity() const { return m_Position - m_LastPosition; }

    void AddVelocity(glm::vec3 v) { m_LastPosition -= v; }

    void SetPositionSameSpeed(const glm::vec3& newPosition)
    {
        const glm::vec3 to_last = m_LastPosition - m_Position;
        m_Position = newPosition;
        m_LastPosition = m_Position + to_last;
    }

    void Move(const glm::vec3& deltaPosition) { m_Position += deltaPosition; }

    MeshBase* GetMesh() const { return p_Mesh; }
    void SetMesh(MeshBase* mesh) { p_Mesh = mesh; }
};