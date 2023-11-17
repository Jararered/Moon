#pragma once

#include <imgui.h>

#include "Scenario.hpp"

namespace Moon
{

    class Panel
    {
    public:
        virtual ~Panel() = default;

        virtual void Update() = 0;

        std::shared_ptr<Scenario> GetScenario() { return s_Scenario.lock(); }

    private:
        static std::weak_ptr<Scenario> s_Scenario;
    };

}