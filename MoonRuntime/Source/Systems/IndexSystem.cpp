#include "IndexSystem.hpp"

#include "Coordinator.hpp"

#include "Components/Index.hpp"
#include "Components/Transform.hpp"

#include <print>

extern Coordinator e_Coordinator;

void IndexSystem::Register()
{
    Signature signature;
    signature.set(e_Coordinator.GetComponentType<Transform>());
    signature.set(e_Coordinator.GetComponentType<Index>());
    e_Coordinator.SetSystemSignature<IndexSystem>(signature);
}

void IndexSystem::Initialize()
{
    m_Scale = 16.0f;
}

void IndexSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        const auto transform = e_Coordinator.GetComponent<Transform>(entity);
        auto& index = e_Coordinator.GetComponent<Index>(entity);
        index = GetIndex(transform.Position, m_Scale);

        // std::print("Position: {}, {}, {}     ", (int)transform.Position.x, (int)transform.Position.y, (int)transform.Position.z);
        // std::println("Index: {}, {}, {}", index.x, index.y, index.z);
    }
}

void IndexSystem::Finalize()
{
}
