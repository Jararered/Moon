#pragma once

#include <Moon.hpp>

#include "ChunkEntity.hpp"
#include "SkyboxEntity.hpp"
#include "SimpleLightEnvironment.hpp"

class Application : public Engine
{
public:
    void Start()
    {
        WindowSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;
        spec.VSync = true;
        spec.API = WindowSpecification::GraphicsAPI::OpenGL;

        auto window = GetWindow(spec);
        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto environment = new SimpleLightEnvironment;
        scenario->SetEnvironment(environment);

        auto camera = new Camera3D;
        camera->SetAspectRatio(spec.Width / spec.Height);
        camera->SetPosition({ 0.0f, 0.0f, 60.0f });
        scenario->SetCamera(camera);

        auto skybox = new SkyboxEntity();
        auto skyboxTexture = Texture();
        auto skyboxShader = Shader();
        auto skyboxMesh = new SkyboxMesh;
        skyboxTexture.Create("Textures/sky.png");
        skyboxShader.Compile("Shaders/Skybox.vert", "Shaders/Skybox.frag");
        skybox->SetMesh(skyboxMesh);
        skybox->GetMesh()->SetTexture(skyboxTexture);
        skybox->GetMesh()->SetShader(skyboxShader);
        skybox->SetPositionReference(&camera->GetPosition());
        scenario->AddEntity(skybox);

        auto blockShader = Shader();
        blockShader.Compile("Shaders/Chunk.vert", "Shaders/Chunk.frag");
        int radius = 4;
        for (int x = -radius; x < radius + 1; x++)
        {
            for (int y = 2; y < 4; y++)
            {
                for (int z = -radius; z < radius + 1; z++)
                {
                    // ChunkManager::AddIndex(glm::vec3(x, y, z));
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