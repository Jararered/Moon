#pragma once

#include <Engine.hpp>
#include <OpenGLWindow.hpp>

#include "CubeMesh.hpp"

// New ECS Implementation
#include <Coordinator.hpp>
#include <Entity.hpp>

#include <Systems/CameraSystem.hpp>
#include <Systems/PhysicsSystem.hpp>
#include <Systems/RenderSystem.hpp>

#include <Components/Camera.hpp>
#include <Components/Collider.hpp>
#include <Components/Gravity.hpp>
#include <Components/Mesh.hpp>
#include <Components/RigidBody.hpp>
#include <Components/Shader.hpp>
#include <Components/Texture.hpp>
#include <Components/Transform.hpp>

#include <glfw/glfw3.h>

Coordinator g_Coordinator;

class Application : public Engine
{
public:
    void Start()
    {
        WindowSpecification spec;
        spec.Width = 1980;
        spec.Height = 1080;
        spec.VSync = true;
        spec.API = WindowSpecification::GraphicsAPI::OpenGL;
        auto window = CreateWindow(spec);

        g_Coordinator.Initialize();
        g_Coordinator.RegisterComponent<Camera>();
        g_Coordinator.RegisterComponent<Gravity>();
        g_Coordinator.RegisterComponent<Mesh>();
        g_Coordinator.RegisterComponent<RigidBody>();
        g_Coordinator.RegisterComponent<Shader>();
        g_Coordinator.RegisterComponent<Collider>();
        g_Coordinator.RegisterComponent<Texture>();
        g_Coordinator.RegisterComponent<Transform>();

        auto renderSystem = g_Coordinator.RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(g_Coordinator.GetComponentType<Mesh>());
            signature.set(g_Coordinator.GetComponentType<Transform>());
            signature.set(g_Coordinator.GetComponentType<Shader>());
            g_Coordinator.SetSystemSignature<RenderSystem>(signature);
        }

        auto cameraSystem = g_Coordinator.RegisterSystem<CameraSystem>();
        {
            Signature signature;
            signature.set(g_Coordinator.GetComponentType<Transform>());
            signature.set(g_Coordinator.GetComponentType<Camera>());
            g_Coordinator.SetSystemSignature<CameraSystem>(signature);
        }

        renderSystem->Initialize();
        cameraSystem->Initialize();

        MeshBase* redCubeMesh = new CubeMesh(glm::vec3(1.0f, 0.0f, 0.0f));
        MeshBase* greenCubeMesh = new CubeMesh(glm::vec3(0.0f, 1.0f, 0.0f));
        MeshBase* blueCubeMesh = new CubeMesh(glm::vec3(0.0f, 0.0f, 1.0f));

        auto shaderID = Shader::CreateShader("Shaders/PositionColor.vert", "Shaders/PositionColor.frag");

        Entity redCubeEntity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(redCubeEntity, Mesh{.p_Mesh = redCubeMesh});
        g_Coordinator.AddComponent<Transform>(redCubeEntity, Transform{.Position = glm::vec3(0.0f), .Rotation = glm::vec3(0.0f), .Scale = glm::vec3(5.0f, 0.1f, 0.1f)});
        g_Coordinator.AddComponent<Shader>(redCubeEntity, Shader{.ID = shaderID});
        Entity greenCubeEntity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(greenCubeEntity, Mesh{.p_Mesh = greenCubeMesh});
        g_Coordinator.AddComponent<Transform>(greenCubeEntity, Transform{.Position = glm::vec3(0.0f), .Rotation = glm::vec3(0.0f), .Scale = glm::vec3(0.1f, 5.0f, 0.1f)});
        g_Coordinator.AddComponent<Shader>(greenCubeEntity, Shader{.ID = shaderID});
        Entity blueCubeEntity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(blueCubeEntity, Mesh{.p_Mesh = blueCubeMesh});
        g_Coordinator.AddComponent<Transform>(blueCubeEntity, Transform{.Position = glm::vec3(0.0f), .Rotation = glm::vec3(0.0f), .Scale = glm::vec3(0.1f, 0.1f, 5.0f)});
        g_Coordinator.AddComponent<Shader>(blueCubeEntity, Shader{.ID = shaderID});

        float m_DeltaFrameTime = 0.0f;

        while (window->IsRunning())
        {
            auto frameStartTime = std::chrono::high_resolution_clock::now();

            Update();

            cameraSystem->Update(m_DeltaFrameTime);

            renderSystem->Update(m_DeltaFrameTime);

            auto frameEndTime = std::chrono::high_resolution_clock::now();
            m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
        }
    }
};