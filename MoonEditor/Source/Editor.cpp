#include "Editor.hpp"

using namespace Moon;

void Editor::CreatePanels()
{
    m_Panels.emplace("Test Panel", std::make_shared<TestPanel>());
}

void Editor::CreatePlatform()
{
    using namespace Moon;

    Entity entity = Entity(m_Scenario);
    entity.AddComponent<Transform>(Transform{.Position = {0, -5, 0}, .Rotation = {0, 0, 0}, .Scale = {10, 1, 10}});
    entity.AddComponent<RigidBody>();
    entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>());
    entity.AddComponent<Texture>(Texture("Resources/Texture/debug.png"));
    entity.AddComponent<Shader>(Shader("Resources/Shader/PositionNormalTexture.vert", "Resources/Shader/Texture.frag"));
}
