#pragma once

#include "System.hpp"

class VerletSystem : public System
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    const unsigned int m_SubStepCount = 2;
};