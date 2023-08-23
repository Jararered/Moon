#pragma once

#include <Moon.hpp>

#include <VerletSystem.hpp>

#include "CubeMesh.hpp"
#include "SquareMesh.hpp"

extern Coordinator g_Coordinator;

class Application : public Engine
{
public:
    void Start()
    {
        // Only initialize systems you intend on using
        p_RenderSystem->Register();
        p_CameraSystem->Register();
        p_VerletSystem->Register();

        CreateBalls();
        CreateCubes();
        // CreatePlatform();

        // Only initialize systems you intend on using
        p_RenderSystem->Initialize();
        p_CameraSystem->Initialize();
        p_VerletSystem->Initialize();

        while (p_Window->IsRunning())
        {
            const auto frameStartTime = std::chrono::high_resolution_clock::now();

            Update();

            p_CameraSystem->Update(m_DeltaFrameTime);

            p_VerletSystem->Update(m_DeltaFrameTime);

            p_RenderSystem->Update(m_DeltaFrameTime);

            const auto frameEndTime = std::chrono::high_resolution_clock::now();
            m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
        }
    }

    void CreateBalls()
    {
        const auto shaderID = Shader::CreateShader("Shaders/PositionColorTexture.vert", "Shaders/PositionColorTexture.frag");
        const auto textureID = Texture::CreateTexture("Textures/Circle.png");
        const float diameter = 5.0f;
        const unsigned int count = 10;
        TMeshBase* mesh = new SquareMesh();

        for (unsigned int i = 0; i < count; i++)
        {
            const float x = Random::Value<float>(-30.0f, 30.0f);
            const float y = Random::Value<float>(-30.0f, 30.0f);

            const Entity entity = g_Coordinator.CreateEntity();
            g_Coordinator.AddComponent<Mesh>(entity, Mesh{.p_Mesh = mesh});
            g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {x, y, 0.0f}, .Rotation = {0.0f, 0.0f, 0.0f}, .Scale = {diameter, diameter, diameter}});
            g_Coordinator.AddComponent<Dynamics>(entity, Dynamics{.Velocity = {0.0f, 0.0f, 0.0f}, .Acceleration = {0.0f, 0.0f, 0.0f}});
            g_Coordinator.AddComponent<Gravity>(entity, Gravity{0.0f, -9.81f * 10.0f, 0.0f});
            g_Coordinator.AddComponent<Verlet>(entity, Verlet{.LastPosition = {x, y, 0.0f}, .Radius = diameter / 2.0f});
            g_Coordinator.AddComponent<Shader>(entity, Shader{.ID = shaderID});
            g_Coordinator.AddComponent<Texture>(entity, Texture{.ID = textureID});
        }
    }

    void CreatePlatform()
    {
        TMeshBase* mesh = new CubeMesh(glm::vec3(1.0f, 0.0f, 0.0f));
        const auto shaderID = Shader::CreateShader("Shaders/PositionColor.vert", "Shaders/PositionColor.frag");

        const Entity entity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(entity, Mesh{.p_Mesh = mesh});
        g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {500, 1, 500}});
        g_Coordinator.AddComponent<Shader>(entity, Shader{.ID = shaderID});
        g_Coordinator.AddComponent<Texture>(entity, Texture{.ID = 0});
    }

    void CreateCubes()
    {
        const float radiusmax = 500;
        const float radiusmin = 400;
        const unsigned int count = 900;

        TMeshBase* mesh = new CubeMesh(glm::vec3(1.0f, 0.0f, 0.0f));
        const auto shaderID = Shader::CreateShader("Shaders/Position.vert", "Shaders/Position.frag");
        for (unsigned int i = 0; i < count; i++)
        {
            const float x = Random::Value<float>(-radiusmax, radiusmax);
            const float y = Random::Value<float>(-radiusmax, radiusmax);
            const float z = Random::Value<float>(-radiusmax, radiusmax);
            const float scale = Random::Value<float>(-10.0f, 10.0f);

            if (x * x + y * y + z * z < radiusmin * radiusmin)
                continue;

            const Entity entity = g_Coordinator.CreateEntity();
            g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {scale, scale, scale}});
            g_Coordinator.AddComponent<Mesh>(entity, Mesh{.p_Mesh = mesh});
            g_Coordinator.AddComponent<Shader>(entity, Shader{.ID = shaderID});
            g_Coordinator.AddComponent<Texture>(entity, Texture{.ID = 0});
        }
    }
};