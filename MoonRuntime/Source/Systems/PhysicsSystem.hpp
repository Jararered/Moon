#pragma once

#include "SystemInterface.hpp"

#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"

#include <glm/vec3.hpp>

class PhysicsSystem final : public SystemInterface
{
public:
    PhysicsSystem() = default;
    PhysicsSystem(const PhysicsSystem&) = delete;
    PhysicsSystem(PhysicsSystem&&) = delete;
    PhysicsSystem& operator=(const PhysicsSystem&) = delete;
    PhysicsSystem& operator=(PhysicsSystem&&) = delete;
    ~PhysicsSystem() override = default;

public:
    void Register(std::shared_ptr<Scenario> scenario) override;
    void Initialize() override;
    void Update(float dt) override;
    void UpdateUI() override;
    void Finalize() override;

private:
    [[nodiscard]] bool IsIntersect(const Transform& transform1, const Transform& transform2);

    void UpdateStep(float dt, EntityID entity);
    void UpdateCollision(float dt, EntityID entity);
    void UpdateFriction(float dt, EntityID entity);

    int m_SubStepCount;
    float m_AirFriction;   // Velocity lost per second due to movement through air
    float m_SolidFriction; // Velocity lost per second due to physical collision
    glm::vec3 m_Gravity;
};