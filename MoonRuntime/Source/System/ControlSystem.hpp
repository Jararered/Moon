#pragma once

#include "Core/Scenario/Scenario.hpp"
#include "Core/Scenario/SystemInterface.hpp"

namespace Moon
{

    class ControlSystem final : public SystemInterface
    {
    public:
        ControlSystem() = default;
        ~ControlSystem() override = default;

    public:
        void Register(std::shared_ptr<Scenario> scenario) override;
        void Initialize() override;
        void Update(float dt) override;
        void Finalize() override;
    };

}