#pragma once

#include <array>
#include <assert.h>
#include <unordered_map>

#include "Entity.hpp"

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArrayTemplate that an entity has been destroyed
// and that it needs to update its array mappings.
class ComponentArrayInterface
{
public:
    virtual ~ComponentArrayInterface() = default;
    virtual void EntityDestroyed(EntityID entity) = 0;
};

template <typename T> class ComponentArrayTemplate : public ComponentArrayInterface
{
public:
    ~ComponentArrayTemplate() override = default;

    void InsertData(EntityID entity, T component)
    {
        assert(!HasData(entity) and "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        const size_t newIndex = m_Size;
        m_EntityToIndexMap[entity] = newIndex;
        m_IndexToEntityMap[newIndex] = entity;
        m_ComponentArray[newIndex] = component;
        m_Size++;
    }

    void RemoveData(EntityID entity)
    {
        assert(HasData(entity) and "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        const size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
        const size_t indexOfLastElement = m_Size - 1;
        m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

        // Update map to point to moved spot
        const EntityID entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
        m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_EntityToIndexMap.erase(entity);
        m_IndexToEntityMap.erase(indexOfLastElement);

        m_Size--;
    }

    [[nodiscard]] T& GetData(EntityID entity)
    {
        assert(HasData(entity) and "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return m_ComponentArray[m_EntityToIndexMap[entity]];
    }

    [[nodiscard]] bool HasData(EntityID entity) { return (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end()); }

    void EntityDestroyed(EntityID entity) override
    {
        // Remove the entity's component if it existed
        if (HasData(entity))
        {
            RemoveData(entity);
        }
    }

private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> m_ComponentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<EntityID, size_t> m_EntityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, EntityID> m_IndexToEntityMap;

    // Total size of valid entries in the array.
    size_t m_Size;
};