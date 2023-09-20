#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

extern Scenario e_Scenario;

class CollisionDemo final : public Engine
{
public:
    void CreateScene()
    {
        // Platform
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>());
            e_Scenario.AddComponent<Shader>(entity, Shader("Shaders/PositionNormalTexture.vert", "Shaders/Gray.frag"));
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {10, 1, 10}});
            // e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}});
        }

        // Box1
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>());
            e_Scenario.AddComponent<Shader>(entity, Shader("Shaders/PositionNormalTexture.vert", "Shaders/Red.frag"));
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {-1, 1, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            // e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}});
        }

        // Box2
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>());
            e_Scenario.AddComponent<Shader>(entity, Shader("Shaders/PositionNormalTexture.vert", "Shaders/Blue.frag"));
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {1, 2, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            // e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}});
        }
    }
};