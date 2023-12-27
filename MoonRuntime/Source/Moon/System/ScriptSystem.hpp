#pragma once

#include "Scenario/Scenario.hpp"
#include "Scenario/SystemInterface.hpp"

namespace Moon
{

    class ScriptSystem final : public SystemInterface
    {
    public:
        ScriptSystem() = default;
        ~ScriptSystem() override = default;

    public:
        void Register(std::shared_ptr<Scenario> scenario) override;
        void Initialize() override;
        void Update(float dt) override;
        void Finalize() override;

    private:
        float m_TimeScale = 1.0f;
    };

}