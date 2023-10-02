#include "Engine.hpp"

#include "OpenGLWindow.hpp"
#include "Scenario.hpp"

#include "Systems/CameraSystem.hpp"
#include "Systems/ControlSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ScriptSystem.hpp"

#include "Component/Camera.hpp"
#include "Component/Control.hpp"
#include "Component/Mesh.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

#include <filesystem>
#include <glfw/glfw3.h>
#include <imgui.h>

void Engine::Initialize()
{
    m_Scenario = std::make_shared<Scenario>();

    m_Scenario->Initialize();
    m_Scenario->RegisterComponent<Camera>();
    m_Scenario->RegisterComponent<Control>();
    m_Scenario->RegisterComponent<Mesh>();
    m_Scenario->RegisterComponent<RigidBody>();
    m_Scenario->RegisterComponent<Script>();
    m_Scenario->RegisterComponent<Shader>();
    m_Scenario->RegisterComponent<Texture>();
    m_Scenario->RegisterComponent<Transform>();

    // Emplace back systems in initialization and update order
    m_SystemMap.emplace(1, m_Scenario->RegisterSystem<ControlSystem>());
    m_SystemMap.emplace(2, m_Scenario->RegisterSystem<CameraSystem>());
    m_SystemMap.emplace(3, m_Scenario->RegisterSystem<ScriptSystem>());
    m_SystemMap.emplace(4, m_Scenario->RegisterSystem<PhysicsSystem>());
    m_SystemMap.emplace(5, m_Scenario->RegisterSystem<RenderSystem>());

    for (const auto [_, system] : m_SystemMap)
    {
        system->Register(m_Scenario);
    }

    for (const auto [_, system] : m_SystemMap)
    {
        system->Initialize();
    }
}

void Engine::Start()
{
    if (!p_Window)
        return;

    while (p_Window->IsRunning())
    {
        const auto frameStartTime = std::chrono::high_resolution_clock::now();

        p_Window->NewFrame();

        ImGui::Begin("Engine Systems", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushItemWidth(100);
        for (const auto [systemID, system] : m_SystemMap)
        {
            if (ImGui::CollapsingHeader(system->m_Name.c_str()))
            {
                system->UpdateUI();
            }

            system->Update(m_DT);
        }

        ImGui::End();

        UpdateUI();

        p_Window->EndFrame();

        const auto frameEndTime = std::chrono::high_resolution_clock::now();
        m_DT = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
    }
}

std::shared_ptr<Window> Engine::CreateWindow(const WindowSpecification& spec)
{
    p_Window = std::make_shared<OpenGLWindow>(spec);
    return p_Window;
}

void Engine::UpdateUI()
{
    static Entity selectedEntity = 0;
    static Transform selectedTransform = Transform{};
    static RigidBody selectedRigidBody = RigidBody{};
    static std::string selectedMesh = "None";
    static std::string selectedTexture = "None";
    static std::string selectedScript = "None";
    static std::string selectedShader = "None";

    ImGui::Begin("Entity Creator", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    auto fmt = std::string("Current entity: ") + std::to_string(selectedEntity);
    ImGui::LabelText("", fmt.c_str());

    ImGui::LabelText("", "Transform");
    ImGui::InputFloat3("Position", &selectedTransform.Position.x);
    ImGui::InputFloat3("Rotation", &selectedTransform.Rotation.x);
    ImGui::InputFloat3("Scale", &selectedTransform.Scale.x);

    ImGui::LabelText("", "Rigid Body");
    ImGui::InputFloat3("Velocity", &selectedRigidBody.Velocity.x);
    ImGui::InputFloat("Mass", &selectedRigidBody.Mass);

    ImGui::LabelText("", "Renderables");
    if (!m_AvaliableMeshesMap.empty())
    {
        if (ImGui::BeginCombo("Avaliable Meshes", selectedMesh.c_str()))
        {
            for (const auto [key, mesh] : m_AvaliableMeshesMap)
            {
                bool is_selected = (selectedMesh == key.c_str());
                if (ImGui::Selectable(key.c_str(), is_selected))
                    selectedMesh = key.c_str();

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    if (!m_AvaliableTexturesMap.empty())
    {
        if (ImGui::BeginCombo("Avaliable Textures", selectedTexture.c_str()))
        {
            for (const auto [key, mesh] : m_AvaliableTexturesMap)
            {
                bool is_selected = (selectedTexture == key.c_str());
                if (ImGui::Selectable(key.c_str(), is_selected))
                    selectedTexture = key.c_str();
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    if (!m_AvaliableScriptsMap.empty())
    {
        if (ImGui::BeginCombo("Avaliable Scripts", selectedScript.c_str()))
        {
            bool is_selected = selectedScript == "None";
            if (ImGui::Selectable("None", is_selected))
                selectedScript = "None";
            for (const auto [key, mesh] : m_AvaliableScriptsMap)
            {
                is_selected = (selectedScript == key.c_str());
                if (ImGui::Selectable(key.c_str(), is_selected))
                    selectedScript = key.c_str();
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    if (!m_AvaliableShadersMap.empty())
    {
        if (ImGui::BeginCombo("Avaliable Shaders", selectedShader.c_str()))
        {
            for (const auto [key, mesh] : m_AvaliableShadersMap)
            {
                bool is_selected = (selectedShader == key.c_str());
                if (ImGui::Selectable(key.c_str(), is_selected))
                    selectedShader = key.c_str();
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }

    if (ImGui::Button("Create Entity"))
    {
        selectedEntity = m_Scenario->CreateEntity();
        m_Scenario->AddComponent<Transform>(selectedEntity, selectedTransform);
        m_Scenario->AddComponent<RigidBody>(selectedEntity, selectedRigidBody);

        if (selectedMesh != "None")
            m_Scenario->AddComponent<Mesh>(selectedEntity, m_AvaliableMeshesMap[selectedMesh]);
        if (selectedTexture != "None")
            m_Scenario->AddComponent<Texture>(selectedEntity, m_AvaliableTexturesMap[selectedTexture]);
        if (selectedScript != "None")
            m_Scenario->AddComponent<Script>(selectedEntity, m_AvaliableScriptsMap[selectedScript]);
        if (selectedShader != "None")
            m_Scenario->AddComponent<Shader>(selectedEntity, m_AvaliableShadersMap[selectedShader]);
    }

    ImGui::End();
}