#pragma once

#include "System.hpp"

#include "Component/Transform.hpp"

#include <glm/vec3.hpp>

class PhysicsSystem final : public System
{
public:
    PhysicsSystem() = default;
    PhysicsSystem(const PhysicsSystem&) = delete;
    PhysicsSystem(PhysicsSystem&&) = delete;
    PhysicsSystem& operator=(const PhysicsSystem&) = delete;
    PhysicsSystem& operator=(PhysicsSystem&&) = delete;
    ~PhysicsSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

    inline static glm::vec3 s_Gravity = glm::vec3(0.0f, -10.0f, 0.0f);

private:
    [[nodiscard]] bool IsIntersect(const Transform& transform1, const Transform& transform2);

    unsigned int m_SubStepCount = 1;

    float m_AirResistance = 0.2f;
};