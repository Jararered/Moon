#include "Demos/CubesFalling.hpp"

int main(int argc, char* argv[])
{
    WindowSpecification spec;
    spec.Width = 1500;
    spec.Height = 750;
    spec.VSync = true;
    spec.API = WindowSpecification::GraphicsAPI::OpenGL;

    CubesFalling app;
    app.CreateWindow(spec);
    app.Initialize();
    app.Start();
}