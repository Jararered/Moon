#include "ScriptSystem.hpp"

#include "Scenario.hpp"
#include "Signature.hpp"

#include "Component/Script.hpp"

#include <print>

extern Scenario e_Scenario;

void ScriptSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Script>());
    e_Scenario.SetSystemSignature<ScriptSystem>(signature);
}

void ScriptSystem::Initialize()
{
}

void ScriptSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        std::println("Entity {} has a script!", entity);
        auto& script = e_Scenario.GetComponent<Script>(entity);
        script->Update(entity, dt);
    }
}

void ScriptSystem::Finalize()
{
}
