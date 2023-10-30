#pragma once

#include "ComponentArray.hpp"
#include "ComponentType.hpp"
#include "UUID.hpp"

#include <memory>
#include <unordered_map>

namespace Moon
{

    class ComponentManager
    {
    public:
        template <typename T> void RegisterComponent()
        {
            assert(!IsRegistered<T>() and "Registering component type more than once.");

            const char* typeName = typeid(T).name();

            // Add this component type to the component type map
            m_ComponentTypes.insert({typeName, m_NextComponentType});

            // Create a ComponentArray pointer and add it to the component arrays map
            m_ComponentArrays.insert({typeName, std::make_shared<ComponentArrayTemplate<T>>()});

            // Increment the value so that the next component registered will be different
            m_NextComponentType++;
        }

        template <typename T> [[nodiscard]] ComponentType GetComponentType()
        {
            assert(IsRegistered<T>() and "Component not registered before use.");

            const char* typeName = typeid(T).name();

            // Return this component's type - used for creating signatures
            return m_ComponentTypes[typeName];
        }

        template <typename T> void AddComponent(UUID uuid, const T& component)
        {
            // Add a component to the array for an uuid
            GetComponentArray<T>()->InsertData(uuid, component);
        }

        template <typename T> void RemoveComponent(UUID uuid)
        {
            // Remove a component from the array for an uuid
            GetComponentArray<T>()->RemoveData(uuid);
        }

        template <typename T> [[nodiscard]] T& GetComponent(UUID uuid)
        {
            // Get a reference to a component from the array for an uuid
            return GetComponentArray<T>()->GetData(uuid);
        }

        // Check for if component array includes uuid
        template <typename T> [[nodiscard]] bool HasComponent(UUID uuid) { return GetComponentArray<T>()->HasData(uuid); }

        template <typename T> [[nodiscard]] bool IsRegistered() { return m_ComponentTypes.find(typeid(T).name()) != m_ComponentTypes.end(); }

        void EntityDestroyed(UUID uuid)
        {
            // Notify each component array that an uuid has been destroyed
            // If it has a component for that uuid, it will remove it
            for (const auto& [_, component] : m_ComponentArrays)
            {
                component->EntityDestroyed(uuid);
            }
        }

    private:
        // Map from type string pointer to a component type
        std::unordered_map<const char*, ComponentType> m_ComponentTypes;

        // Map from type string pointer to a component array
        std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>> m_ComponentArrays;

        // The component type to be assigned to the next registered component - starting at 0
        ComponentType m_NextComponentType;

        // Convenience function to get the statically casted pointer to the ComponentArray of type T.
        template <typename T> std::shared_ptr<ComponentArrayTemplate<T>> GetComponentArray()
        {
            const char* typeName = typeid(T).name();

            assert(IsRegistered<T>() and "Component not registered before use.");

            return std::static_pointer_cast<ComponentArrayTemplate<T>>(m_ComponentArrays[typeName]);
        }
    };

}