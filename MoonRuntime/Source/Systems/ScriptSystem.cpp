#include "ScriptSystem.hpp"

#include "Scenario.hpp"
#include "Signature.hpp"

#include "Component/Script.hpp"

#include <glm/glm.hpp>

extern Scenario e_Scenario;

void ScriptSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Script>());
    e_Scenario.SetSystemSignature<ScriptSystem>(signature);
}

void ScriptSystem::Initialize()
{
    m_Name = "Script System";
}

void ScriptSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        auto& script = e_Scenario.GetComponent<Script>(entity);
        script->Update(entity, m_TimeScale * dt);
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
