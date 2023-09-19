#include "Demos/ChunkDemo.hpp"
#include "Demos/CubesFalling.hpp"
#include "Demos/TexturedCubeDemo.hpp"

int main(int argc, char* argv[])
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = true;
    spec.Title = "Moon (OpenGL)";

    ChunkDemo app;
    app.CreateWindow(spec);
    app.Initialize();

    app.CreateScene();

    app.Start();
}