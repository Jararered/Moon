#pragma once

#include "System.hpp"

#include <glm/vec3.hpp>

class PhysicsSystem final : public System
{
public:
    PhysicsSystem() = default;
    PhysicsSystem(const PhysicsSystem&) = default;
    PhysicsSystem(PhysicsSystem&&) = default;
    PhysicsSystem& operator=(const PhysicsSystem&) = default;
    PhysicsSystem& operator=(PhysicsSystem&&) = default;
    ~PhysicsSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

    inline static glm::vec3 s_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);

private:
    [[nodiscard]] bool IsIntersect(const glm::vec3& lower1, const glm::vec3& upper1, const glm::vec3& lower2, const glm::vec3& upper2);

    unsigned int m_SubStepCount = 1;
};