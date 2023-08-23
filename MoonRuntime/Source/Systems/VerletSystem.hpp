#pragma once

#include "System.hpp"

class VerletSystem : public System
{
public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    const unsigned int m_SubStepCount = 2;
};