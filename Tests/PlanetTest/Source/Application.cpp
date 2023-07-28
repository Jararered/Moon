#include "Application.hpp"

#include "ChunkEntity.hpp"
#include "SimpleLightEnvironment.hpp"

void Application::Start()
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
    scenario->SetCamera(camera);

    auto shader = Shader();
    shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

    int radius = 3;
    for (int x = -radius; x < radius + 1; x++)
    {
        for (int y = -radius; y < radius + 1; y++)
        {
            for (int z = -radius; z < radius + 1; z++)
            {
                ChunkData* chunkData = new ChunkData();
                chunkData->Allocate();
                chunkData->SetChunkIndex({x, y, z});
                chunkData->GeneratePlanet();

                auto mesh = new ChunkMesh();
                mesh->CreateMesh(chunkData);

                Entity* entity = new ChunkEntity();
                entity->SetMesh(mesh);
                entity->GetMesh()->SetShader(shader);
                scenario->AddEntity(entity);



                // Entity* entity = new ChunkEntity({ x, y, z });
                // scenario->AddEntity(entity);
                // entity->GetMesh()->SetShader(shader);
            }
        }
    }

    renderer->Add(scenario);

    while (window->IsRunning())
    {
        Engine::Update();
    }
}