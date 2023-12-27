#pragma once

#include <Scenario/Scenario.hpp>

#include <imgui.h>

namespace Moon
{

    struct Panel
    {
        virtual void Update() = 0;

    protected:
        virtual ~Panel() = default;

    private:
        std::shared_ptr<Scenario> GetScenario() { return s_CurrentScenario.lock(); }
        static std::weak_ptr<Scenario> s_CurrentScenario;
    };

}