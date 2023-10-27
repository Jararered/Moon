#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

class Scenario
{
public:
    void Initialize()
    {
        // Create pointers to each manager
        m_ComponentManager = std::make_unique<ComponentManager>();
        m_EntityManager = std::make_unique<EntityManager>();
        m_SystemManager = std::make_unique<SystemManager>();
    }

    [[nodiscard]] UUID CreateEntity()
    {
        // UUID methods
        return m_EntityManager->CreateEntity();
    }

    void DestroyEntity(UUID uuid)
    {
        m_EntityManager->DestroyEntity(uuid);
        m_ComponentManager->EntityDestroyed(uuid);
        m_SystemManager->EntityDestroyed(uuid);
    }

    template <typename T> void RegisterComponent()
    {
        // Component methods
        m_ComponentManager->RegisterComponent<T>();
    }

    template <typename T> void AddComponent(UUID uuid, const T& component)
    {
        m_ComponentManager->AddComponent<T>(uuid, component);

        auto signature = m_EntityManager->GetSignature(uuid);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(uuid, signature);

        m_SystemManager->EntitySignatureChanged(uuid, signature);
    }

    // Added for adding components using the default constructor of the component
    template <typename T> void AddComponent(UUID uuid)
    {
        m_ComponentManager->AddComponent<T>(uuid, T());

        auto signature = m_EntityManager->GetSignature(uuid);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(uuid, signature);

        m_SystemManager->EntitySignatureChanged(uuid, signature);
    }

    template <typename T> void RemoveComponent(UUID uuid)
    {
        m_ComponentManager->RemoveComponent<T>(uuid);

        auto signature = m_EntityManager->GetSignature(uuid);
        signature.set(m_ComponentManager->GetComponentType<T>(), false);
        m_EntityManager->SetSignature(uuid, signature);

        m_SystemManager->EntitySignatureChanged(uuid, signature);
    }

    template <typename T> [[nodiscard]] T& GetComponent(UUID uuid) { return m_ComponentManager->GetComponent<T>(uuid); }

    template <typename T> [[nodiscard]] ComponentType GetComponentType() { return m_ComponentManager->GetComponentType<T>(); }

    // Check for if uuid has component type
    template <typename T> [[nodiscard]] bool HasComponent(UUID uuid) { return m_ComponentManager->HasComponent<T>(uuid); }

    // System methods
    template <typename T> [[nodiscard]] std::shared_ptr<T> RegisterSystem() { return m_SystemManager->RegisterSystem<T>(); }

    template <typename T> void SetSystemSignature(Signature signature) { m_SystemManager->SetSignature<T>(signature); }

private:
    std::unique_ptr<ComponentManager> m_ComponentManager;
    std::unique_ptr<EntityManager> m_EntityManager;
    std::unique_ptr<SystemManager> m_SystemManager;
};