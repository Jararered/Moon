#include "IndexSystem.hpp"

#include "Scenario.hpp"

#include "Component/Index.hpp"
#include "Component/Transform.hpp"

#include <print>

extern Scenario e_Scenario;

void IndexSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Transform>());
    signature.set(e_Scenario.GetComponentType<Index>());
    e_Scenario.SetSystemSignature<IndexSystem>(signature);
}

void IndexSystem::Initialize()
{
    m_Scale = 16.0f;
}

void IndexSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        const auto transform = e_Scenario.GetComponent<Transform>(entity);
        auto& index = e_Scenario.GetComponent<Index>(entity);
        index = GetIndex(transform.Position, m_Scale);

        // std::print("Position: {}, {}, {}     ", (int)transform.Position.x, (int)transform.Position.y, (int)transform.Position.z);
        // std::println("Index: {}, {}, {}", index.x, index.y, index.z);
    }
}

void IndexSystem::Finalize()
{
}
