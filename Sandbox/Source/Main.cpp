#include "Demos/CubesFalling.hpp"
#include "Demos/TexturedCubeDemo.hpp"

int main(int argc, char* argv[])
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = true;
    spec.Title = "Moon (OpenGL)";

    TexturedCubeDemo app;
    app.CreateWindow(spec);
    app.Initialize();

    // Spawn random cubes
    app.CreateScene();

    app.Start();
}