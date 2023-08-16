#pragma once

#include <Moon.hpp>

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
        auto window = Engine::CreateWindow(spec);

        g_Coordinator.Initialize();
        g_Coordinator.RegisterComponent<Camera>();
        g_Coordinator.RegisterComponent<Gravity>();
        g_Coordinator.RegisterComponent<Mesh>();
        g_Coordinator.RegisterComponent<RigidBody>();
        g_Coordinator.RegisterComponent<Shader>();
        g_Coordinator.RegisterComponent<CircleCollider>();
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

        int radius = 4;
        for (int x = -radius; x < radius + 1; x++)
        {
            for (int y = -radius; y < radius + 1; y++)
            {
                for (int z = -radius; z < radius + 1; z++)
                {
                    // Entity* entity = new ChunkEntity();
                    // entity->SetPosition(glm::vec3(x, y, z));
                    // ChunkData* chunkData = new ChunkData(glm::vec3(x, y, z));
                    // auto mesh = new ChunkMesh(chunkData);
                    // entity->SetMesh(mesh);
                    // entity->GetMesh()->SetShader(shader);
                    // scenario->AddEntity(entity);
                }
            }
        }

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