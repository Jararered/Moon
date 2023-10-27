#pragma once

#include <array>
#include <assert.h>
#include <unordered_map>

#include "UUID.hpp"

namespace Moon
{

    class ComponentArrayInterface
    {
    public:
        virtual ~ComponentArrayInterface() = default;
        virtual void EntityDestroyed(UUID uuid) = 0;
    };

    template <typename T> class ComponentArrayTemplate : public ComponentArrayInterface
    {
    public:
        ~ComponentArrayTemplate() override = default;

        void InsertData(UUID uuid, T component)
        {
            assert(!HasData(uuid) and "Component added to same uuid more than once.");

            // Put new entry at end and update the maps
            const size_t newIndex = m_Size;
            m_EntityToIndexMap[uuid] = newIndex;
            m_IndexToEntityMap[newIndex] = uuid;
            m_ComponentArray[newIndex] = component;
            m_Size++;
        }

        void RemoveData(UUID uuid)
        {
            assert(HasData(uuid) and "Removing non-existent component.");

            // Copy element at end into deleted element's place to maintain density
            const size_t indexOfRemovedEntity = m_EntityToIndexMap[uuid];
            const size_t indexOfLastElement = m_Size - 1;
            m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

            // Update map to point to moved spot
            const UUID entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
            m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            m_EntityToIndexMap.erase(uuid);
            m_IndexToEntityMap.erase(indexOfLastElement);

            m_Size--;
        }

        [[nodiscard]] T& GetData(UUID uuid)
        {
            assert(HasData(uuid) and "Retrieving non-existent component.");

            // Return a reference to the uuid's component
            return m_ComponentArray[m_EntityToIndexMap[uuid]];
        }

        [[nodiscard]] bool HasData(UUID uuid) { return (m_EntityToIndexMap.find(uuid) != m_EntityToIndexMap.end()); }

        void EntityDestroyed(UUID uuid) override
        {
            // Remove the uuid's component if it existed
            if (HasData(uuid))
            {
                RemoveData(uuid);
            }
        }

    private:
        // The packed array of components (of generic type T),
        // set to a specified maximum amount, matching the maximum number
        // of entities allowed to exist simultaneously, so that each uuid
        // has a unique spot.
        std::array<T, MAX_UUIDS> m_ComponentArray;

        // Map from an uuid ID to an array index.
        std::unordered_map<UUID, size_t> m_EntityToIndexMap;

        // Map from an array index to an uuid ID.
        std::unordered_map<size_t, UUID> m_IndexToEntityMap;

        // Total size of valid entries in the array.
        size_t m_Size;
    };

}