#pragma once

#include "System.hpp"

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
    [[nodiscard]] bool IsIntersect(const glm::vec3& lower1, const glm::vec3& upper1, const glm::vec3& lower2, const glm::vec3& upper2);

    unsigned int m_SubStepCount = 1;
};