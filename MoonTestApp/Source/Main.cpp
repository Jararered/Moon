#include <Moon.hpp>

#include <Tests.hpp>

int main(int argc, char* argv[])
{
    Engine engine;

    auto window = engine.CreateWindow(GraphicsAPI::OpenGL);
    auto& renderer = window->CreateRenderer();

    auto camera = new Camera2D;
    renderer.AddCamera(camera);

    Shader* shader = new Shader;
    shader->Compile("Shaders/Position.vert", "Shaders/Colors/Red.frag");
    camera->AttachShader(shader);

    int size = 5;
    for (int i = -size; i < size + 1; i++)
    {
        for (int j = -size; j < size + 1; j++)
        {
            Mesh* mesh = ExampleMesh::Square({ i * 100.0f, j * 100.0f }, 50.0f);
            renderer.AddMesh(mesh);
        }
    }

    while (window->IsRunning())
    {
        engine.Update();
    }
}