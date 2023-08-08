#pragma once

#include <vector>

#include "Scenario.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void Update(float dt);
    void Render();

    void SetScenario(Scenario* scenario)
    {
        if (p_Scenario)
            delete p_Scenario;
        p_Scenario = scenario;
    }

private:
    Scenario* p_Scenario = nullptr;

public:
    void PollDebugControls();
    void EnableWireframes() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    void DisableWireframes() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    void EnableBackCulling() { glEnable(GL_CULL_FACE); }
    void DisableBackCulling() { glDisable(GL_CULL_FACE); }
};