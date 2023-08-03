#pragma once

#include <Moon.hpp>

#include "ChunkEntity.hpp"

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

        auto window = GetWindow(spec);
        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto camera = new Camera3D;
        camera->SetAspectRatio(spec.Width / spec.Height);
        camera->SetPosition({ 0.0f, 0.0f, 60.0f });
        camera->SetSkybox("Textures/sky.png");
        scenario->SetCamera(camera);

        auto blockShader = Shader();
        blockShader.Compile("Shaders/Chunk.vert", "Shaders/Chunk.frag");
        int radius = 4;
        for (int x = -radius; x < radius + 1; x++)
        {
            for (int y = 2; y < 4; y++)
            {
                for (int z = -radius; z < radius + 1; z++)
                {
                    ChunkData* chunkData = new ChunkData(glm::vec3(x, y, z));
                    auto mesh = new ChunkMesh(chunkData);
                    Entity* entity = new ChunkEntity();
                    entity->SetMesh(mesh);
                    entity->GetMesh()->SetShader(blockShader);
                    scenario->AddEntity(entity);
                }
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};