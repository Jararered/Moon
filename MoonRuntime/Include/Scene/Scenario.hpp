#pragma once

#include <vector>

#include "Camera.hpp"
#include "Entity.hpp"

class Scenario
{
public:
    Scenario() = default;
    virtual ~Scenario() = default;

    void Update(float dt)
    {
        if (p_Camera)
            p_Camera->Update(dt);

        for (auto entity : m_Entities)
            entity->Update(dt);
    }

private:
    Camera* p_Camera;

    std::vector<Entity*> m_Entities;

public:
    Camera* GetCamera() const { return p_Camera; }
    void SetCamera(Camera* camera) { p_Camera = camera; }

    void AddEntity(Entity* entity) { m_Entities.push_back(entity); }
    std::vector<Entity*> GetEntities() const { return m_Entities; }
};