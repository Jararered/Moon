#pragma once

#include "Entity.hpp"

#include <vector>

class Dynamics
{
public:
    Dynamics() = default;

    void ApplyGravity(const std::vector<Entity*>& entities)
    {
        for (auto entity : entities)
        {
            entity->ApplyAcceleration(m_Gravity);
        }
    }

    void CheckCollisions(std::vector<Entity*> entities, float dt)
    {
        float responseCoefficient = 0.75f;
        uint64_t objectCount = entities.size();
        // Iterate on all objects
        for (uint64_t i = 0; i < objectCount; ++i)
        {
            Entity* entity1 = entities[i];
            // Iterate on object involved in new collision pairs
            for (uint64_t k = i + 1; k < objectCount; ++k)
            {
                Entity* entity2 = entities[k];
                glm::vec3 v = entity1->GetPosition() - entity2->GetPosition();
                float dist2 = v.x * v.x + v.y * v.y + v.z * v.z;
                float min_dist = entity1->GetRadius() + entity2->GetRadius();

                // Check overlapping
                if (dist2 < min_dist * min_dist)
                {
                    float dist = sqrt(dist2);
                    glm::vec3 n = v / dist;
                    float mass_ratio_1 = entity1->GetRadius() / (entity1->GetRadius() + entity2->GetRadius());
                    float mass_ratio_2 = entity2->GetRadius() / (entity1->GetRadius() + entity2->GetRadius());
                    float delta = 0.5f * responseCoefficient * (dist - min_dist);

                    // Update positions
                    // entity1.position = entity1.position - n * (mass_ratio_2 * delta);
                    entity1->SetPosition(entity1->GetPosition() - n * (mass_ratio_2 * delta));
                    entity1->SetPosition(entity1->GetPosition() - n * (mass_ratio_2 * delta));
                    // entity2.position = entity2.position + n * (mass_ratio_1 * delta);
                    entity2->SetPosition(entity2->GetPosition() + n * (mass_ratio_1 + delta));
                    entity2->SetPosition(entity2->GetPosition() + n * (mass_ratio_1 + delta));
                }
            }
        }
    }

protected:
    glm::vec3 m_Gravity = { 0.0f, 0.0f, 0.0f };
};