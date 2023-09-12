#pragma once

#include <array>
#include <unordered_map>

#include "Entity.hpp"

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.

using Component = size_t;

class ComponentArrayInterface
{
public:
    virtual ~ComponentArrayInterface() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template <typename T> class ComponentArrayTemplate final : public ComponentArrayInterface
{
public:
    void InsertData(Entity entity, T component)
    {
        // Put new entry at end and update the maps
        const size_t newIndex = m_Size;
        m_EntityToIndexArray[entity] = newIndex;
        m_IndexToEntityArray[newIndex] = entity;
        m_ComponentArray[newIndex] = component;
        m_Size++;
    }

    void RemoveData(Entity entity)
    {
        // Copy element at end into deleted element's place to maintain density
        const size_t indexOfRemovedEntity = m_EntityToIndexArray[entity];
        const size_t indexOfLastElement = m_Size - 1;
        m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

        // Update map to point to moved spot
        const Entity entityOfLastElement = m_IndexToEntityArray[indexOfLastElement];
        m_EntityToIndexArray[entityOfLastElement] = indexOfRemovedEntity;
        m_IndexToEntityArray[indexOfRemovedEntity] = entityOfLastElement;

        m_EntityToIndexArray[entity] = 0;
        m_IndexToEntityArray[indexOfLastElement] = 0;

        m_Size--;
    }

    T& GetData(Entity entity)
    {
        // Return a reference to the entity's component
        return m_ComponentArray[m_EntityToIndexArray[entity]];
    }

    void EntityDestroyed(Entity entity) override
    {
        for (const auto entityIndex : m_EntityToIndexArray)
        {
            if (entity = entityIndex)
            {
                RemoveData(entity);
            }
        }
    }

private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> m_ComponentArray;

    std::array<Entity, MAX_ENTITIES> m_EntityToIndexArray;
    std::array<Component, MAX_ENTITIES> m_IndexToEntityArray;

    // Total size of valid entries in the array.
    size_t m_Size;
};