#include <Moon.hpp>

#include <Tests.hpp>

int main(int argc, char* argv[])
{
    Engine engine;

    auto window = engine.CreateWindow(GraphicsAPI::OpenGL);
    auto& renderer = window->CreateRenderer();

    auto& camera = renderer.Create2DCamera();

    Mesh* mesh = ExampleMesh::Square();
    renderer.AddMesh(mesh);

    while (window->IsRunning())
    {
        engine.Update();
    }
}