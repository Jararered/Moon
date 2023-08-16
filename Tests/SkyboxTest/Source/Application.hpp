#pragma once

#include <Moon.hpp>

#include "ChunkMesh.hpp"

extern Coordinator g_Coordinator;

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
        g_Coordinator.RegisterComponent<Mesh>();
        g_Coordinator.RegisterComponent<Shader>();
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

        auto shaderID = Shader::CreateShader("Shaders/Chunk.vert", "Shaders/Chunk.frag");

        int radius = 2;

        ManualTimer timer("World generation");
        timer.Start();
        for (int x = -radius; x < radius; x++)
        {
            for (int y = -radius; y < radius; y++)
            {
                for (int z = -radius; z < radius; z++)
                {
                    ScopedTimer timer("Chunk generation");

                    ChunkData* chunkData = new ChunkData({x, y, z});
                    MeshBase* chunk = new ChunkMesh(chunkData);

                    Entity chunkEntity = g_Coordinator.CreateEntity();
                    g_Coordinator.AddComponent<Mesh>(chunkEntity, Mesh{.p_Mesh = chunk});
                    g_Coordinator.AddComponent<Transform>(chunkEntity,
                                                          Transform{.Position = {x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE}, .Rotation = {0.0f, 0.0f, 0.0f}, .Scale = {1.0f, 1.0f, 1.0f}});
                    g_Coordinator.AddComponent<Shader>(chunkEntity, Shader{.ID = shaderID});

                    delete chunkData;
                }
            }
        }
        timer.Stop();

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