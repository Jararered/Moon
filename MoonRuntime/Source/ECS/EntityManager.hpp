#pragma once

#include <array>
#include <assert.h>
#include <bitset>
#include <queue>

#include "Entity.hpp"
#include "Signature.hpp"

class EntityManager
{
public:
    EntityManager()
    {
        // Initialize the queue with all possible entity IDs
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_AvailableEntities.push(entity);
        }
    }

    Entity CreateEntity()
    {
        assert(m_LivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

        // Take an ID from the front of the queue
        Entity id = m_AvailableEntities.front();
        m_AvailableEntities.pop();
        ++m_LivingEntityCount;

        return id;
    }

    void DestroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Invalidate the destroyed entity's signature
        m_Signatures[entity].reset();

        // Put the destroyed ID at the back of the queue
        m_AvailableEntities.push(entity);
        --m_LivingEntityCount;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Put this entity's signature into the array
        m_Signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Get this entity's signature from the array
        return m_Signatures[entity];
    }

private:
    // Queue of unused entity IDs
    std::queue<Entity> m_AvailableEntities{};

    // Array of signatures where the index corresponds to the entity ID
    std::array<Signature, MAX_ENTITIES> m_Signatures{};

    // Total living entities - used to keep limits on how many exist
    uint32_t m_LivingEntityCount{};
};