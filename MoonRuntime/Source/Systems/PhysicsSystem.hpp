#pragma once

#include "System.hpp"

class PhysicsSystem : public System
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    unsigned int m_SubStepCount = 4;
};