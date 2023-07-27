#pragma once

#include "Environment.hpp"
#include "Camera.hpp"
#include "Entity.hpp"

#include <vector>

class Scenario
{
public:
    Scenario() = default;
    virtual ~Scenario() = default;

    void Update(float dt)
    {
        if (p_Environment)
            p_Environment->Update(dt);

        if (p_Camera)
            p_Camera->Update(dt);

        for (auto entity : m_Entities)
            entity->Update(dt);
    }

    Environment* GetEnvironment() const { return p_Environment; }
    void SetEnvironment(Environment* environment) { p_Environment = environment; }

    Camera* GetCamera() const { return p_Camera; }
    void SetCamera(Camera* camera) { p_Camera = camera; }

    void AddEntity(Entity* entity) { m_Entities.push_back(entity); }
    // TODO Search through vector and remove entity
    void RemoveEntity(Entity* entity) {};

    std::vector<Entity*> GetEntities() const { return m_Entities; }

private:
    Environment* p_Environment;
    Camera* p_Camera;
    std::vector<Entity*> m_Entities;
};