#pragma once

#include "Core/Scenario/Scenario.hpp"
#include "Core/Scenario/UUID.hpp"
#include "Structure/MeshInterface.hpp"

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <stb_image.h>

#include <assert.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace Moon
{
    using Mesh = std::shared_ptr<MeshInterface>;

    class ScriptInterface
    {
    public:
        virtual void Update(float dt, UUID uuid) = 0;

        std::shared_ptr<Scenario> GetScenario() { return s_Scenario.lock(); }

    private:
        static std::weak_ptr<Scenario> s_Scenario;
    };

    using Script = std::weak_ptr<ScriptInterface>;

    struct Camera
    {
        glm::mat4 ViewMatrix = glm::mat4(0.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(0.0f);
        float FOV = 0.0f;
        float Aspect = 0.0f;
    };

    struct Transform
    {
        glm::vec3 Position = glm::vec3(0.0f); // Meter
        glm::vec3 Rotation = glm::vec3(0.0f); // Radian
        glm::vec3 Scale = glm::vec3(1.0f);    // Scalar

        void FixRotation(float& rotation)
        {
            // rotation in radians
            while (rotation > glm::radians(360.0f))
                rotation -= glm::radians(360.0f);
            while (rotation < glm::radians(-360.0f))
                rotation += glm::radians(360.0f);
        }

        void Reset()
        {
            Position = glm::vec3(0.0f);
            Rotation = glm::vec3(0.0f);
            Scale = glm::vec3(1.0f);
        }
    };

    struct RigidBody
    {
        enum Status
        {
            None = 0,
            Grounded = 1,
            Falling = 2
        };

        glm::vec3 Velocity = glm::vec3(0.0f);
        glm::vec3 Acceleration = glm::vec3(0.0f);
        float Mass = 0.0f;
        int MovementStatus = Status::Falling;
    };

    struct Controller
    {
        float SpeedLimit = 0.0f;
        float JumpMagnitude = 5.0f;
        float WalkMagnitude = 5.0f;
    };

    struct Texture
    {
        unsigned int ID = 0;

        Texture() = default;
        Texture(std::string_view textureFile)
        {
            int width = 0;
            int height = 0;
            int channels = 0;

            stbi_set_flip_vertically_on_load(true);

            auto data = stbi_load(textureFile.data(), &width, &height, &channels, 0);
            if (not data)
            {
                return;
            }

            glGenTextures(1, &ID);
            glBindTexture(GL_TEXTURE_2D, ID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };

}