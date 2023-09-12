#include "Demos/CubesFalling.hpp"

int main(int argc, char* argv[])
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = true;
    spec.Title = "Moon (OpenGL)";

    CubesFalling app;
    app.CreateWindow(spec);
    app.Initialize();
    app.Start();
}