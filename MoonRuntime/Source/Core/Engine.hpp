#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "Scenario.hpp"
#include "SystemInterface.hpp"
#include "Window.hpp"

#include "Components/Camera.hpp"
#include "Components/Controller.hpp"
#include "Components/Mesh.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Script.hpp"
#include "Components/Shader.hpp"
#include "Components/Texture.hpp"
#include "Components/Transform.hpp"

enum EngineStatus
{
    Initialized,
    Uninitialized
};

namespace Moon
{
class Engine
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    std::shared_ptr<Window> CreateWindow(const WindowSpecification& spec);

    void Initialize();
    void Start();

    void UpdateUI();

protected:
    float m_DT = 0.0f;

    std::shared_ptr<Scenario> m_Scenario;

    std::shared_ptr<Window> p_Window;
    EngineStatus m_Status = EngineStatus::Uninitialized;

    std::vector<std::shared_ptr<SystemInterface>> m_Systems;
    std::map<unsigned int, std::shared_ptr<SystemInterface>> m_SystemMap;

    std::unordered_map<std::string, std::shared_ptr<MeshInterface>> m_AvaliableMeshesMap;
    std::unordered_map<std::string, Script> m_AvaliableScriptsMap;
    std::unordered_map<std::string, Texture> m_AvaliableTexturesMap;
    std::unordered_map<std::string, Shader> m_AvaliableShadersMap;
};
}