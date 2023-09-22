#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

extern Scenario e_Scenario;

class CollisionDemo final : public Engine
{
public:
    void CreateScene()
    {
        const auto cube = std::make_shared<TexturedCubeMesh>();
        const auto staticShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        const auto texture = Texture("Textures/checker.png");

        // Floor
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            e_Scenario.AddComponent<RigidBody>(entity);
        }

        // Platforms
        for (unsigned int i = 0; i < 200; i++)
        {
            Transform transform;
            transform.Position = glm::vec3(Random::Value<float>(-10, 10), Random::Value<float>(0, 10), Random::Value<float>(-10, 10));
            transform.Scale = glm::vec3(Random::Value<float>(0.5, 3), Random::Value<float>(0.2, 0.2), Random::Value<float>(0.5, 3));

            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, transform);
            e_Scenario.AddComponent<RigidBody>(entity);
        }
    }
};