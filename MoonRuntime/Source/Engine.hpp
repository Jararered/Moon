#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "Scenario.hpp"
#include "SystemInterface.hpp"
#include "Window.hpp"

#include "Component/Camera.hpp"
#include "Component/Control.hpp"
#include "Component/Mesh.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

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

    std::vector<std::shared_ptr<SystemInterface>> m_Systems;
    std::map<unsigned int, std::shared_ptr<SystemInterface>> m_SystemMap;

    std::unordered_map<std::string, std::shared_ptr<MeshInterface>> m_AvaliableMeshesMap;
    std::unordered_map<std::string, Script> m_AvaliableScriptsMap;
    std::unordered_map<std::string, Texture> m_AvaliableTexturesMap;
    std::unordered_map<std::string, Shader> m_AvaliableShadersMap;
};