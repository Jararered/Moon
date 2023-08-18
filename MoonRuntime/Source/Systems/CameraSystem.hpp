#pragma once

#include "System.hpp"

class CameraSystem : public System
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;
};