#include "App/Editor.hpp"

using namespace Moon;

int main()
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = true;
    spec.Title = "Moon (OpenGL)";

    Editor editor;
    editor.CreateWindow(spec);
    editor.CreateScene();
    editor.Start();
}