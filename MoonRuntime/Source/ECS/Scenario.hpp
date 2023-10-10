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

    [[nodiscard]] EntityID CreateEntity()
    {
        // Entity methods
        return m_EntityManager->CreateEntity();
    }

    void DestroyEntity(EntityID entity)
    {
        m_EntityManager->DestroyEntity(entity);
        m_ComponentManager->EntityDestroyed(entity);
        m_SystemManager->EntityDestroyed(entity);
    }

    template <typename T> void RegisterComponent()
    {
        // Component methods
        m_ComponentManager->RegisterComponent<T>();
    }

    template <typename T> void AddComponent(EntityID entity, const T& component)
    {
        m_ComponentManager->AddComponent<T>(entity, component);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    // Added for adding components using the default constructor of the component
    template <typename T> void AddComponent(EntityID entity)
    {
        m_ComponentManager->AddComponent<T>(entity, T());

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T> void RemoveComponent(EntityID entity)
    {
        m_ComponentManager->RemoveComponent<T>(entity);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), false);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T> [[nodiscard]] T& GetComponent(EntityID entity) { return m_ComponentManager->GetComponent<T>(entity); }

    template <typename T> [[nodiscard]] ComponentType GetComponentType() { return m_ComponentManager->GetComponentType<T>(); }

    // Check for if entity has component type
    template <typename T> bool HasComponent(EntityID entity) { return m_ComponentManager->HasComponent<T>(entity); }

    // System methods
    template <typename T> [[nodiscard]] std::shared_ptr<T> RegisterSystem() { return m_SystemManager->RegisterSystem<T>(); }

    template <typename T> void SetSystemSignature(Signature signature) { m_SystemManager->SetSignature<T>(signature); }

private:
    std::unique_ptr<ComponentManager> m_ComponentManager;
    std::unique_ptr<EntityManager> m_EntityManager;
    std::unique_ptr<SystemManager> m_SystemManager;
};