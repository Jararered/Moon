#include "App/Editor.hpp"

int main()
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = false;
    spec.Title = "Moon (OpenGL)";

    Editor editor;
    editor.CreateWindow(spec);
    editor.CreateScene();
    editor.Start();
}