#include <Engine.hpp>

int main()
{
    Engine engine;

    auto &window = engine.CreateWindow();
    auto &renderer = window.CreateRenderer();
    auto &camera = renderer.CreateCamera();

    while (true)
    {
        engine.Update();
    }
}