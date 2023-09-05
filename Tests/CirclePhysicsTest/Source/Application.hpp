#pragma once

#include <Moon.hpp>

#include "CubeMesh.hpp"
#include "SquareMesh.hpp"

extern Coordinator g_Coordinator;

class Application : public Engine
{
public:
    void Start()
    {
        // Only initialize systems you intend on using
        p_PhysicsSystem->Register();
        p_CameraSystem->Register();
        p_RenderSystem->Register();

        CreateCubes();
        CreatePlatform();

        // Only initialize systems you intend on using
        p_PhysicsSystem->Initialize();
        p_CameraSystem->Initialize();
        p_RenderSystem->Initialize();

        while (p_Window->IsRunning())
        {
            const auto frameStartTime = std::chrono::high_resolution_clock::now();

            Update();

            p_PhysicsSystem->Update(m_DeltaFrameTime);
            p_CameraSystem->Update(m_DeltaFrameTime);
            p_RenderSystem->Update(m_DeltaFrameTime);

            const auto frameEndTime = std::chrono::high_resolution_clock::now();
            m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
        }
    }

    void CreatePlatform()
    {
        std::shared_ptr<DrawableMesh> mesh = std::make_shared<CubeMesh>(glm::vec3(0.5f, 0.5f, 0.5f));
        const auto shaderID = Shader::CreateShader("Shaders/PositionColor.vert", "Shaders/PositionColor.frag");

        const Entity entity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(entity, Mesh{.Data = mesh});
        g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {500, 1, 500}});
        g_Coordinator.AddComponent<Shader>(entity, Shader{.ID = shaderID});
        g_Coordinator.AddComponent<Texture>(entity, Texture{.ID = 0});
    }

    void CreateCubes()
    {
        const unsigned int count = 100;

        std::shared_ptr<DrawableMesh> mesh = std::make_shared<CubeMesh>(glm::vec3(1.0f, 0.0f, 0.0f));
        const auto shaderID = Shader::CreateShader("Shaders/Position.vert", "Shaders/Position.frag");
        for (unsigned int i = 0; i < count; i++)
        {
            // const float x = Random::Value<float>(-100.0f, 100.0f);
            // const float y = Random::Value<float>(20.0f, 100.0f);
            // const float z = Random::Value<float>(-100.0f, 100.0f);
            const float x = 0, y = 10, z = 0;
            const float scale = Random::Value<float>(1, 10);

            const Entity entity = g_Coordinator.CreateEntity();
            g_Coordinator.AddComponent<Mesh>(entity, Mesh{.Data = mesh});
            g_Coordinator.AddComponent<Shader>(entity, Shader{.ID = shaderID});
            g_Coordinator.AddComponent<Texture>(entity, Texture{.ID = 0});
            g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, scale, 1}});
            g_Coordinator.AddComponent<Dynamics>(entity, Dynamics{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}});
        }
    }
};