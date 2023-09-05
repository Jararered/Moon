#pragma once

#include "System.hpp"

#include <glm/vec3.hpp>

class PhysicsSystem : public System
{
public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

    inline static glm::vec3 s_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);

private:
    unsigned int m_SubStepCount = 1;
};