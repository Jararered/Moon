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
        auto shaderID = Shader::CreateShader("Shaders/PositionColorTexture.vert", "Shaders/PositionColorTexture.frag");
        auto textureID = Texture::CreateTexture("Textures/Circle.png");
        float diameter = 5.0f;
        unsigned int count = 50;

        for (unsigned int i = 0; i < count; i++)
        {
            float randomx = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (20.0f + 20.0f));
            float randomy = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (20.0f + 20.0f));
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            std::cout << randomx << ", " << randomy << "\n";

            Entity ball = g_Coordinator.CreateEntity();
            MeshBase* mesh = new SquareMesh(glm::vec3(r, g, b));
            g_Coordinator.AddComponent<Mesh>(ball, Mesh{.p_Mesh = mesh});
            g_Coordinator.AddComponent<Transform>(ball, Transform{.Position = {randomx, randomy, 0.0f}, .Rotation = {0.0f, 0.0f, 0.0f}, .Scale = {diameter, diameter, diameter}});
            g_Coordinator.AddComponent<RigidBody>(ball, RigidBody{.LastPosition = {randomx, randomy, 0.0f}});
            g_Coordinator.AddComponent<Gravity>(ball, Gravity{.Force = {0.0f, -9.81f * 10.0f, 0.0f}});
            g_Coordinator.AddComponent<Collider>(ball, Collider{.Radius = diameter / 2.0f});
            g_Coordinator.AddComponent<Shader>(ball, Shader{.ID = shaderID});
            g_Coordinator.AddComponent<Texture>(ball, Texture{.ID = textureID});
        }

        while (p_Window->IsRunning())
        {
            auto frameStartTime = std::chrono::high_resolution_clock::now();

            Update();

            p_CameraSystem->Update(m_DeltaFrameTime);
            p_VerletSystem->Update(m_DeltaFrameTime);
            p_RenderSystem->Update(m_DeltaFrameTime);

            auto frameEndTime = std::chrono::high_resolution_clock::now();
            m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
        }
    }
};