#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Meshes/Square.hpp"

#include "Utilities/TextureMap.hpp"

class CubesFalling final : public Engine
{
public:
    void CreateScene()
    {
        const unsigned int count = 200;

        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/Normal.frag");
        for (unsigned int i = 0; i < count; i++)
        {
            const float x = Random::Value<float>(-20, 20);
            const float y = Random::Value<float>(0, 200);
            const float z = Random::Value<float>(-20, 20);
            const float random = Random::Value<float>(1, 10);

            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, mesh);
            m_Scenario->AddComponent<Shader>(entity, shader);
            m_Scenario->AddComponent<Texture>(entity, Texture());
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, random, 1}});
            m_Scenario->AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}, .Mass = 1.0f});
        }

        // Floor
        {
            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, mesh);
            m_Scenario->AddComponent<Shader>(entity, shader);
            m_Scenario->AddComponent<Texture>(entity);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {40, 1, 40}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
    }
};