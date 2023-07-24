#include <Moon.hpp>

int main(int argc, char* argv[])
{
    Engine engine;

    auto window = engine.CreateWindow(GraphicsAPI::OpenGL);
    auto& renderer = window->CreateRenderer();

    auto& camera = renderer.Create2DCamera();
    auto& mesh = renderer.CreateTestMesh();

    while (window->IsRunning())
    {
        engine.Update();
    }
}