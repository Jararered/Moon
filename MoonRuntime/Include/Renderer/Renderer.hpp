#pragma once

#include "Scenario.hpp"

#include <vector>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Reset();
    void Update(float dt);
    void Render(Scenario* scenario);

    void Add(Scenario* scenario) { m_Scenarios.push_back(scenario); }

private:
    std::vector<Scenario*> m_Scenarios;
};