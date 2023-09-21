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
        const auto staticShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/Normal.frag");

        // Floor
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            e_Scenario.AddComponent<RigidBody>(entity);
        }

        // Walls
        {
            const Entity wall1 = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(wall1, cube);
            e_Scenario.AddComponent<Shader>(wall1, staticShader);
            e_Scenario.AddComponent<Texture>(wall1);
            e_Scenario.AddComponent<Transform>(wall1, Transform{.Position = {0, 5, 10}, .Rotation = {0, 0, 0}, .Scale = {20, 10, 1}});
            e_Scenario.AddComponent<RigidBody>(wall1);

            const Entity wall2 = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(wall2, cube);
            e_Scenario.AddComponent<Shader>(wall2, staticShader);
            e_Scenario.AddComponent<Texture>(wall2);
            e_Scenario.AddComponent<Transform>(wall2, Transform{.Position = {0, 5, -10}, .Rotation = {0, 0, 0}, .Scale = {20, 10, 1}});
            e_Scenario.AddComponent<RigidBody>(wall2);

            const Entity wall3 = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(wall3, cube);
            e_Scenario.AddComponent<Shader>(wall3, staticShader);
            e_Scenario.AddComponent<Texture>(wall3);
            e_Scenario.AddComponent<Transform>(wall3, Transform{.Position = {10, 5, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 10, 20}});
            e_Scenario.AddComponent<RigidBody>(wall3);

            const Entity wall4 = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(wall4, cube);
            e_Scenario.AddComponent<Shader>(wall4, staticShader);
            e_Scenario.AddComponent<Texture>(wall4);
            e_Scenario.AddComponent<Transform>(wall4, Transform{.Position = {-10, 5, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 10, 20}});
            e_Scenario.AddComponent<RigidBody>(wall4);
        }

        // Dynamic Cubes
        const auto blueShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/Blue.frag");
        for (unsigned int i = 0; i < 0; i++)
        {
            const auto randomX = Random::Value<float>(-8, 8);
            const auto randomY = Random::Value<float>(2, 8);
            const auto randomZ = Random::Value<float>(-8, 8);

            const auto velocityX = Random::Value<float>(5, 10);
            const auto velocityZ = Random::Value<float>(5, 10);

            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, blueShader);
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {randomX, randomY, randomZ}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{velocityX, 0, velocityZ}, .Acceleration{0, 0, 0}, .Mass = 1.0f});
        }
    }
};