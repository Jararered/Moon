#pragma once

#include "Environment.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "Dynamics.hpp"

#include <vector>

class Scenario
{
public:
    Scenario() = default;
    virtual ~Scenario() = default;

    void Update(float dt)
    {
        if (p_Environment)
        {
            p_Environment->Update(dt);
        }

        if (p_Camera)
        {
            p_Camera->Update(dt);
        }

        // for (auto entity : m_Entities)
        // {
        //     entity->UpdateDynamics(dt);
        // }

        for (auto entity : m_Entities)
        {
            entity->Update(dt);
        }
    }

private:
    Environment* p_Environment;
    Camera* p_Camera;
    Dynamics* p_Dynamics;

    std::vector<Entity*> m_Entities;

public:
    Environment* GetEnvironment() const { return p_Environment; }
    void SetEnvironment(Environment* environment) { p_Environment = environment; }

    Camera* GetCamera() const { return p_Camera; }
    void SetCamera(Camera* camera) { p_Camera = camera; }

    Dynamics* GetDynamics() const { return p_Dynamics; }
    void SetDynamics(Dynamics* dynamics) { p_Dynamics = dynamics; }

    void AddEntity(Entity* entity) { m_Entities.push_back(entity); }
    std::vector<Entity*> GetEntities() const { return m_Entities; }
};