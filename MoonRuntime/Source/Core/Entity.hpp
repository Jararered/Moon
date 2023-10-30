#pragma once

#include "Scenario.hpp"
#include "UUID.hpp"

#include <memory>

namespace Moon
{

    class Entity
    {
    public:
        Entity(std::shared_ptr<Scenario> scenario) : m_Scenario(scenario) { m_UUID = m_Scenario->CreateEntity(); }
        ~Entity() {}

        // Returns true if the entity has the component
        template <class T> bool HasComponent() { return m_Scenario->HasComponent<T>(m_UUID); }

        // Adds a default-constructed component provided
        template <class T> void AddComponent() { m_Scenario->AddComponent<T>(m_UUID); }

        // Adds the component provided
        template <class T> void AddComponent(const T& component) { m_Scenario->AddComponent<T>(m_UUID, component); }

        // Removes the component provided
        template <class T> void RemoveComponent() { m_Scenario->RemoveComponent<T>(m_UUID); }

    private:
        std::shared_ptr<Scenario> m_Scenario;
        UUID m_UUID;
    };

}