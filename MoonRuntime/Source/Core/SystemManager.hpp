#pragma once

#include "Signature.hpp"
#include "SystemInterface.hpp"
#include "UUID.hpp"

#include <assert.h>
#include <memory>
#include <unordered_map>

namespace Moon
{

    class SystemManager
    {
    public:
        template <typename T> [[nodiscard]] std::shared_ptr<T> RegisterSystem()
        {
            assert(!IsRegistered<T>() and "Registering system more than once.");

            // Create a pointer to the system and return it so it can be used externally
            const char* typeName = typeid(T).name();
            const auto system = std::make_shared<T>();
            m_Systems.insert({typeName, system});

            return system;
        }

        template <typename T> void SetSignature(Signature signature)
        {
            assert(IsRegistered<T>() and "System used before registered.");

            // Set the signature for this system
            const char* typeName = typeid(T).name();
            m_Signatures.insert({typeName, signature});
        }

        void EntityDestroyed(UUID uuid)
        {
            // Erase a destroyed uuid from all system lists
            // m_UUIDs is a set so no check needed
            for (const auto& [_, system] : m_Systems)
            {
                system->m_UUIDs.erase(uuid);
            }
        }

        void EntitySignatureChanged(UUID uuid, Signature entitySignature)
        {
            // Notify each system that an uuid's signature changed
            for (const auto& [type, system] : m_Systems)
            {
                const auto& systemSignature = m_Signatures[type];

                if ((entitySignature & systemSignature) == systemSignature)
                {
                    // Entity signature matches system signature - insert into set
                    system->m_UUIDs.insert(uuid);
                }
                else
                {
                    // Entity signature does not match system signature - erase from set
                    system->m_UUIDs.erase(uuid);
                }
            }
        }

        template <typename T> [[nodiscard]] bool IsRegistered() { return m_Systems.find(typeid(T).name()) != m_Systems.end(); }

    private:
        // Map from system type string pointer to a signature
        std::unordered_map<const char*, Signature> m_Signatures{};

        // Map from system type string pointer to a system pointer
        std::unordered_map<const char*, std::shared_ptr<SystemInterface>> m_Systems{};
    };

}