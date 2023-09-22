#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Meshes/Square.hpp"

#include "Utilities/TextureMap.hpp"

extern Scenario e_Scenario;

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

            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, mesh);
            e_Scenario.AddComponent<Shader>(entity, shader);
            e_Scenario.AddComponent<Texture>(entity, Texture());
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, random, 1}});
            e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}, .Mass = 1.0f});
        }

        // Floor
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, mesh);
            e_Scenario.AddComponent<Shader>(entity, shader);
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {40, 1, 40}});
            e_Scenario.AddComponent<RigidBody>(entity);
        }
    }
};