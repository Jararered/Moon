#include "ScriptSystem.hpp"

#include "Moon/Components.hpp"

#include <glm/glm.hpp>

using namespace Moon;

void ScriptSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(scenario->GetComponentType<Script>());
    signature.set(scenario->GetComponentType<Transform>());
    scenario->SetSystemSignature<ScriptSystem>(signature);
}

void ScriptSystem::Initialize()
{
}

void ScriptSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        auto& script = m_Scenario->GetComponent<Script>(entity);
        script->Update(dt * m_TimeScale, entity);
    }
}

void ScriptSystem::Finalize()
{
}
