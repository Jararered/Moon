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
        const unsigned int count = 9999;

        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shaderID = Shader("Shaders/PositionNormalTexture.vert", "Shaders/White.frag");
        for (unsigned int i = 0; i < count; i++)
        {
            const float x = Random::Value<float>(-100, 100);
            const float y = Random::Value<float>(0, 10000);
            const float z = Random::Value<float>(-100, 100);
            const float random = Random::Value<float>(1, 10);

            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, mesh);
            e_Scenario.AddComponent<Shader>(entity, shaderID);
            e_Scenario.AddComponent<Texture>(entity, Texture());
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, random, 1}});
            e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}});
        }
    }
};