#pragma once

#include <imgui.h>

#include <Core/Scenario/Scenario.hpp>

namespace Moon
{

    struct Panel
    {
        virtual void Update() = 0;

    protected:
        virtual ~Panel() = default;

    private:
        std::shared_ptr<Scenario> GetScenario() { return s_Scenario.lock(); }
        static std::weak_ptr<Scenario> s_Scenario;
    };

}