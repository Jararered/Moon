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
        const auto blueShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/Normal.frag");
        for (unsigned int i = 0; i < 200; i++)
        {
            const auto randX = Random::Value<float>(-10, 10);
            const auto randY = Random::Value<float>(0, 10);
            const auto randZ = Random::Value<float>(-10, 10);

            const auto randScaleX = Random::Value<float>(0.2, 2);
            const auto randScaleY = Random::Value<float>(0.2, 2);
            const auto randScaleZ = Random::Value<float>(0.2, 2);

            const auto randVelocityX = Random::Value<float>(5, 10);
            const auto randVelocityZ = Random::Value<float>(5, 10);

            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, blueShader);
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {randX, randY, randZ}, .Rotation = {0, 0, 0}, .Scale = {randScaleX, randScaleY, randScaleZ}});
            e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{randVelocityX, 0, randVelocityZ}, .Acceleration{0, 0, 0}, .Mass = 0.0f});
        }
    }
};