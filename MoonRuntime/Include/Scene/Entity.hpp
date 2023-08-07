#pragma once

#include "CircleCollider.hpp"
#include "Mesh.hpp"

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void Update(float dt) {}

    virtual void UpdateDynamics(float dt)
    {
        m_LastPosition = m_Position;
        const glm::vec3 new_pos = m_Position + (dt * m_Velocity) + (0.5f * dt * dt * m_Acceleration);
        const glm::vec3 new_acc = m_Acceleration;
        const glm::vec3 new_vel = m_Velocity + (m_Acceleration + new_acc) * (dt * 0.5f);
        m_Position = new_pos;
        m_Velocity = new_vel;
        m_Acceleration = {0.0f, 0.0f, 0.0f};

        // Updates the mesh's location
        if (p_Mesh)
            p_Mesh->SetTranslationMatrix(glm::translate(glm::mat4(1.0f), m_Position));
    }

protected:
    MeshBase* p_Mesh = nullptr;
    CircleCollider* p_Collider = nullptr;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_LastPosition = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Velocity = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Acceleration = {0.0f, 0.0f, 0.0f};
    float m_Mass = 1.0f;

public:
    void ApplyAcceleration(const glm::vec3& acceleration) { m_Acceleration += acceleration; }

    glm::vec3 GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& Position)
    {
        m_Position = Position;
        if (p_Mesh)
            p_Mesh->SetTranslationMatrix(glm::translate(glm::mat4(1.0f), m_Position));
    }

    glm::vec3 GetVelocity() const { return m_Velocity; }
    void SetVelocity(const glm::vec3& Velocity) { m_Velocity = Velocity; }

    glm::vec3 GetAcceleration() const { return m_Acceleration; }
    void SetAcceleration(const glm::vec3& Acceleration) { m_Acceleration = Acceleration; }

    MeshBase* GetMesh() const { return p_Mesh; }
    void SetMesh(MeshBase* mesh) { p_Mesh = mesh; }

    CircleCollider* GetCollider() const { return p_Collider; }
    void SetCollider(CircleCollider* collider) { p_Collider = collider; }

    float GetMass() const { return m_Mass; }
    void SetMass(float mass) { m_Mass = mass; }

    glm::vec3 GetLastPosition() const { return m_LastPosition; }
    void SetLastPosition(const glm::vec3& lastPosition) { m_LastPosition = lastPosition; }
};