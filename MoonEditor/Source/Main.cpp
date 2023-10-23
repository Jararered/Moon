#include "Demos/Demo.hpp"

int main()
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = false;
    spec.Title = "Moon (OpenGL)";

    Demo app;
    app.CreateWindow(spec);
    app.CreateScene();

    app.Start();
}