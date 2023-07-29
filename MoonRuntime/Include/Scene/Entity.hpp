#pragma once

#include "Mesh.hpp"
#include "Collider.hpp"

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void Update(float dt) {}

    virtual void UpdateDynamics(float dt)
    {
        glm::vec3 displacement = m_Position - m_LastPosition;

        m_LastPosition = m_Position;
        // m_Velocity = ((m_Position + displacement) / dt) + (m_Acceleration * dt);
        m_Position = m_Position + displacement + (m_Acceleration * dt * dt);

        m_Acceleration = { 0.0f, 0.0f, 0.0f };

        // Updates the mesh's location with the entity's position
        glm::mat4 translation = glm::mat4(1.0f);
        translation = glm::translate(translation, m_Position);
        p_Mesh->SetTranslationMatrix(translation);
    }

    void ApplyAcceleration(const glm::vec3& acceleration) { m_Acceleration = m_Acceleration + acceleration; }
    void SetVelocity(const glm::vec3& velocity, float dt) { m_LastPosition = m_Position - (velocity * dt); }
    void ApplyVelocity(const glm::vec3& velocity, float dt) { m_LastPosition = m_LastPosition - (velocity * dt); }
    glm::vec3 GetVelocity(float dt) { return (m_Position - m_LastPosition) / dt; }

protected:
    Mesh* p_Mesh = nullptr;
    Collider* p_Collider = nullptr;

    float m_Radius = 1.0f;
    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_LastPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Acceleration = { 0.0f, 0.0f, 0.0f };

public:
    glm::vec3 GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

    glm::vec3 GetAcceleration() const { return m_Acceleration; }
    void SetAcceleration(const glm::vec3& acceleration) { m_Acceleration = acceleration; }

    Mesh* GetMesh() const { return p_Mesh; }
    void SetMesh(Mesh* mesh) { p_Mesh = mesh; }

    Collider* GetCollider() const { return p_Collider; }
    void SetPCollider(Collider* collider) { p_Collider = collider; }

    float GetRadius() const { return m_Radius; }
    void SetRadius(float radius) { m_Radius = radius; }

};