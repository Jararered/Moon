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
        for (auto entity : m_Entities)
            entity->Update(dt);

        UpdateCollisions(dt);

        UpdateBoundaries(dt);

        if (p_Camera)
            p_Camera->Update(dt);
    }

    void UpdateCollisions(float dt)
    {
        for (auto entity1 : m_Entities)
        {
            for (auto entity2 : m_Entities)
            {
                if (entity1 != entity2)
                {
                    glm::vec3 position1 = entity1->GetPosition();
                    glm::vec3 position2 = entity2->GetPosition();

                    float damp = 0.75f;
                    glm::vec3 collisionAxis = position1 - position2;
                    float distance = glm::length(collisionAxis);
                    float minDistance = entity1->GetCollider()->Radius + entity2->GetCollider()->Radius;
                    if (distance > minDistance)
                        continue;

                    std::cout << "Collision!\n";

                    glm::vec3 v1 = entity1->GetVelocity();
                    glm::vec3 v2 = entity2->GetVelocity();

                    float m1 = entity1->GetMass();
                    float m2 = entity2->GetMass();

                    float vmag1 = glm::length(((m1 - m2) / (m1 + m2)) * v1 + ((m2 + m2) / (m1 + m2)) * v2);
                    glm::vec3 dir1 = glm::normalize(-collisionAxis);
                    float vmag2 = glm::length(((m2 + m2) / (m1 + m2)) * v1 + ((m2 - m1) / (m1 + m2)) * v2);
                    glm::vec3 dir2 = glm::normalize(collisionAxis);

                    entity1->SetVelocity(damp * vmag1 * dir1);
                    entity2->SetVelocity(damp * vmag2 * dir2);

                    entity1->SetPosition(entity1->GetLastPosition());
                    entity2->SetPosition(entity2->GetLastPosition());
                }
            }
        }
    }

    void UpdateBoundaries(float dt)
    {
        float damp = 0.75f;
        for (auto entity : m_Entities)
        {
            float posy = 1080.0f / 2.0f;
            float negy = -1080.0f / 2.0f;
            float posx = 1920.0f / 2.0f;
            float negx = -1920.0f / 2.0f;

            glm::vec3 position = entity->GetPosition();
            glm::vec3 lastPosition = entity->GetLastPosition();
            glm::vec3 velocity = entity->GetVelocity() * damp;
            float radius = entity->GetCollider()->Radius;

            if (position.x + radius > posx)
            {
                entity->SetVelocity({-velocity.x, velocity.y, velocity.z});
                entity->SetPosition(lastPosition);
                std::cout << "Collision!\n";
            }
            if (position.x - radius < negx)
            {
                entity->SetVelocity({-velocity.x, velocity.y, velocity.z});
                entity->SetPosition(lastPosition);
                std::cout << "Collision!\n";
            }
            if (position.y + radius > posy)
            {
                entity->SetVelocity({velocity.x, -velocity.y, velocity.z});
                entity->SetPosition(lastPosition);
                std::cout << "Collision!\n";
            }
            if (position.y - radius < negy)
            {
                entity->SetVelocity({velocity.x, -velocity.y, velocity.z});
                entity->SetPosition(lastPosition);
                std::cout << "Collision!\n";
            }
        }
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