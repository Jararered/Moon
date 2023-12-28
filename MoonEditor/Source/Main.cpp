#include "Editor.hpp"

using namespace Moon;

int main()
{
    WindowSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    spec.VSync = true;
    spec.Title = "Moon (OpenGL)";

    // Application
    Editor editor;

    // Creating window
    editor.CreateWindow(spec);
    editor.InitializeImGui();

    // Test Scene
    editor.CreatePlatform();

    editor.Start();
}