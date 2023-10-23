#include "ScriptSystem.hpp"

#include "Core/Scenario.hpp"
#include "Core/Signature.hpp"

#include "Component/Script.hpp"
#include "Component/Transform.hpp"

#include <glm/glm.hpp>

void ScriptSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(m_Scenario->GetComponentType<Script>());
    signature.set(m_Scenario->GetComponentType<Transform>());
    m_Scenario->SetSystemSignature<ScriptSystem>(signature);
}

void ScriptSystem::Initialize()
{
    m_Name = "Script System";
}

void ScriptSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        auto& script = m_Scenario->GetComponent<Script>(entity);
        script->Update(m_Scenario, entity, m_TimeScale * dt);
    }
}

void ScriptSystem::UpdateUI()
{
    if (ImGui::InputFloat("Time Scale", &m_TimeScale, 0.1f, 1.0f))
        m_TimeScale = glm::clamp(m_TimeScale, 0.0f, 100'000'000.f);
}

void ScriptSystem::Finalize()
{
}
