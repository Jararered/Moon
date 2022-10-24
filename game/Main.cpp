#include <Engine.hpp>

int main()
{
    Engine engine;

    auto &window = engine.CreateWindow();
    auto &renderer = window.CreateRenderer();
    auto &camera = renderer.CreateCamera();

    auto &mesh = renderer.CreateTestMesh();

    while (window.IsRunning())
    {
        engine.Update();
    }
}