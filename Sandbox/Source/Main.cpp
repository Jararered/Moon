#include "Demos/ChunkDemo.hpp"
#include "Demos/CollisionDemo.hpp"
#include "Demos/CubesFalling.hpp"
#include "Demos/ScriptDemo.hpp"
#include "Demos/StairsDemo.hpp"
#include "Demos/TexturedCubeDemo.hpp"

int main(int argc, char* argv[])
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = true;
    spec.Title = "Moon (OpenGL)";

    ScriptDemo app;
    app.CreateWindow(spec);
    app.Initialize();

    app.CreateScene();

    app.Start();
}