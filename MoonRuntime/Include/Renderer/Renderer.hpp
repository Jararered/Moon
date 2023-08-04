#pragma once

#include <vector>

#include "Scenario.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void Update(float dt);
    void PollDebugControls();

    void Add(Scenario* scenario) { m_Scenarios.push_back(scenario); }
    void Render(Scenario* scenario);

private:
    std::vector<Scenario*> m_Scenarios;

public:
    void EnableWireframes() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    void DisableWireframes() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    void EnableBackCulling() { glEnable(GL_CULL_FACE); }
    void DisableBackCulling() { glDisable(GL_CULL_FACE); }
};