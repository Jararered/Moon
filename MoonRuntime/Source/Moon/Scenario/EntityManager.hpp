#pragma once

#include "Signature.hpp"
#include "UUID.hpp"

#include <array>
#include <bitset>
#include <queue>

namespace Moon
{

    class EntityManager
    {
    public:
        EntityManager()
        {
            // Initialize the queue with all possible UUIDs
            for (UUID uuid = 0; uuid < MAX_UUIDS; uuid++)
            {
                m_AvailableEntities.push(uuid);
            }
        }

        [[nodiscard]] UUID CreateEntity()
        {
            // Take an ID from the front of the queue
            const UUID id = m_AvailableEntities.front();
            m_AvailableEntities.pop();
            m_ActiveEntityCount++;

            return id;
        }

        void DestroyEntity(UUID uuid)
        {
            // Invalidate the destroyed UUID's signature
            m_Signatures[uuid].reset();

            // Put the destroyed ID at the back of the queue
            m_AvailableEntities.push(uuid);
            m_ActiveEntityCount--;
        }

        void SetSignature(UUID uuid, Signature signature)
        {
            // Put this uuid's signature into the array
            m_Signatures[uuid] = signature;
        }

        [[nodiscard]] Signature GetSignature(UUID uuid)
        {
            // Get this uuid's signature from the array
            return m_Signatures[uuid];
        }

    private:
        // Queue of unused uuid IDs
        std::queue<UUID> m_AvailableEntities;

        // Array of signatures where the index corresponds to the uuid ID
        std::array<Signature, MAX_UUIDS> m_Signatures;

        // Total living entities - used to keep limits on how many exist
        uint32_t m_ActiveEntityCount;
    };

}