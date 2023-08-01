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
        camera->SetPosition({ 0.0f, 0.0f, 0.0f });
        scenario->SetCamera(camera);

        auto skyboxShader = Shader();
        skyboxShader.Compile("Shaders/BasicTexture.vert", "Shaders/BasicTexture.frag");

        auto texture = Texture();
        texture.Create("Textures/sky.png");

        auto mesh = new SkyboxMesh;
        auto skybox = new SkyboxEntity();
        skybox->SetMesh(mesh);
        skybox->GetMesh()->SetTexture(texture);
        skybox->GetMesh()->SetShader(skyboxShader);
        skybox->SetPositionReference(&camera->GetPosition());
        scenario->AddEntity(skybox);

        auto blockShader = Shader();
        blockShader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");
        int radius = 3;
        for (int x = -radius; x < radius + 1; x++)
        {
            for (int y = 0; y < 2; y++)
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