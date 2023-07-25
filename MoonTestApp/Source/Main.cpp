#include <Moon.hpp>

#include <Tests.hpp>

int main(int argc, char* argv[])
{
    Engine engine;

    auto window = engine.CreateWindow(GraphicsAPI::OpenGL);
    auto& renderer = window->CreateRenderer();

    auto camera = renderer.Create2DCamera();

    Mesh* mesh1 = ExampleMesh::Square({100.0f, 0.0f}, 100.0f);
    Mesh* mesh2 = ExampleMesh::Square({-100.0f, 0.0f}, 100.0f);
    renderer.AddMesh(mesh1);
    renderer.AddMesh(mesh2);

    while (window->IsRunning())
    {
        engine.Update();
    }
}