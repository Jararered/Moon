#pragma once

#include "SystemInterface.hpp"

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

    inline static glm::vec3 s_Gravity = glm::vec3(0.0f, -10.0f, 0.0f);

private:
    [[nodiscard]] bool IsIntersect(const Transform& transform1, const Transform& transform2);

    int m_SubStepCount = 1;
    float m_AirFriction = 5.0f;    // Velocity lost per second due to movement through air
    float m_SolidFriction = 30.0f; // Velocity lost per second due to physical collision
};