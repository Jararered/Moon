#pragma once

#include <vector>

#include "Scenario.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void ClearBuffer();
    void Update(float dt);
    void Render(Scenario* scenario);

    void Add(Scenario* scenario) { m_Scenarios.push_back(scenario); }

private:
    std::vector<Scenario*> m_Scenarios;
};