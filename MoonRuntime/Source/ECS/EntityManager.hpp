#pragma once

#include "Entity.hpp"
#include "Signature.hpp"

#include <array>
#include <bitset>
#include <queue>

class EntityManager
{
public:
    EntityManager()
    {
        // Initialize the queue with all possible entity IDs
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
        {
            m_AvailableEntities.push(entity);
        }
    }

    [[nodiscard]] Entity CreateEntity()
    {
        // Take an ID from the front of the queue
        const Entity id = m_AvailableEntities.front();
        m_AvailableEntities.pop();
        m_ActiveEntityCount++;

        return id;
    }

    void DestroyEntity(Entity entity)
    {
        // Invalidate the destroyed entity's signature
        m_Signatures[entity].reset();

        // Put the destroyed ID at the back of the queue
        m_AvailableEntities.push(entity);
        m_ActiveEntityCount--;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        // Put this entity's signature into the array
        m_Signatures[entity] = signature;
    }

    [[nodiscard]] Signature GetSignature(Entity entity)
    {
        // Get this entity's signature from the array
        return m_Signatures[entity];
    }

private:
    // Queue of unused entity IDs
    std::queue<Entity> m_AvailableEntities;

    // Array of signatures where the index corresponds to the entity ID
    std::array<Signature, MAX_ENTITIES> m_Signatures;

    // Total living entities - used to keep limits on how many exist
    uint32_t m_ActiveEntityCount;
};