#pragma once

#include <Moon.hpp>

#include <VerletSystem.hpp>

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

        const auto shaderID = Shader::CreateShader("Shaders/PositionColorTexture.vert", "Shaders/PositionColorTexture.frag");
        const auto textureID = Texture::CreateTexture("Textures/Circle.png");
        const float diameter = 5.0f;
        const unsigned int count = 10;
        TMeshBase* mesh = new SquareMesh();

        for (unsigned int i = 0; i < count; i++)
        {
            const float x = Random::Value<float>(-30.0f, 30.0f);
            const float y = Random::Value<float>(-30.0f, 30.0f);

            const Entity ball = g_Coordinator.CreateEntity();
            g_Coordinator.AddComponent<Mesh>(ball, Mesh{.p_Mesh = mesh});
            g_Coordinator.AddComponent<Transform>(ball, Transform{.Position = {x, y, 0.0f}, .Rotation = {0.0f, 0.0f, 0.0f}, .Scale = {diameter, diameter, diameter}});
            g_Coordinator.AddComponent<RigidBody>(ball, RigidBody{.LastPosition = {x, y, 0.0f}});
            g_Coordinator.AddComponent<Gravity>(ball, Gravity{0.0f, -9.81f * 10.0f, 0.0f});
            g_Coordinator.AddComponent<Collider>(ball, Collider{.Radius = diameter / 2.0f});
            g_Coordinator.AddComponent<Shader>(ball, Shader{.ID = shaderID});
            g_Coordinator.AddComponent<Texture>(ball, Texture{.ID = textureID});
        }

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
};