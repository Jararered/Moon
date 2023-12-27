#pragma once

#include "Moon/Scenario/Scenario.hpp"
#include "Moon/Scenario/UUID.hpp"
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

        std::shared_ptr<Scenario> GetScenario() { return s_CurrentScenario.lock(); }

    private:
        static std::weak_ptr<Scenario> s_CurrentScenario;
    };

    using Script = std::shared_ptr<ScriptInterface>;

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

    struct Shader
    {
        unsigned int ID = 0;

        Shader() = default;
        Shader(std::string_view vertexPath, std::string_view fragmentPath)
        {
            // Vertex Shader
            auto vertexID = glCreateShader(GL_VERTEX_SHADER);
            auto vertexSource = OpenFile(vertexPath);
            auto vertexSourceChar = vertexSource.c_str();
            glShaderSource(vertexID, 1, &vertexSourceChar, NULL);
            glCompileShader(vertexID);
            if (!CheckCompileStatus(vertexID))
                return;

            // Fragment Shader
            auto fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
            auto fragmentSource = OpenFile(fragmentPath);
            auto fragmentSourceChar = fragmentSource.c_str();
            glShaderSource(fragmentID, 1, &fragmentSourceChar, NULL);
            glCompileShader(fragmentID);
            if (!CheckCompileStatus(fragmentID))
                return;

            // Linking
            auto shaderID = glCreateProgram();
            glAttachShader(shaderID, vertexID);
            glAttachShader(shaderID, fragmentID);
            glLinkProgram(shaderID);
            if (!CheckLinkingStatus(shaderID))
                return;

            glDeleteShader(vertexID);
            glDeleteShader(fragmentID);

            assert(shaderID != 0 and "Shader::Create: Unable to compile shader. No valid shader id was received from the GPU.");

            ID = shaderID;
        }

        Shader(std::string_view vertexPath, std::string_view geometryPath, std::string_view fragmentPath)
        {
            // Vertex Shader
            auto vertexID = glCreateShader(GL_VERTEX_SHADER);
            auto vertexSource = OpenFile(vertexPath);
            auto vertexSourceChar = vertexSource.c_str();
            glShaderSource(vertexID, 1, &vertexSourceChar, NULL);
            glCompileShader(vertexID);
            if (!CheckCompileStatus(vertexID))
                return;

            // Geometry Shader
            auto geometryID = glCreateShader(GL_GEOMETRY_SHADER);
            auto geometrySource = OpenFile(geometryPath);
            auto geometrySourceChar = geometrySource.c_str();
            glShaderSource(geometryID, 1, &geometrySourceChar, NULL);
            glCompileShader(geometryID);
            if (!CheckCompileStatus(geometryID))
                return;

            // Fragment Shader
            auto fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
            auto fragmentSource = OpenFile(fragmentPath);
            auto fragmentSourceChar = fragmentSource.c_str();
            glShaderSource(fragmentID, 1, &fragmentSourceChar, NULL);
            glCompileShader(fragmentID);
            if (!CheckCompileStatus(fragmentID))
                return;

            // Linking
            auto shaderID = glCreateProgram();
            glAttachShader(shaderID, vertexID);
            glAttachShader(shaderID, geometryID);
            glAttachShader(shaderID, fragmentID);
            glLinkProgram(shaderID);
            CheckLinkingStatus(shaderID);

            glDeleteShader(vertexID);
            glDeleteShader(geometryID);
            glDeleteShader(fragmentID);

            assert(shaderID != 0 and "Shader::Create: Unable to compile shader. No valid shader id was received from the GPU.");

            ID = shaderID;
        }

        std::string OpenFile(std::string_view file)
        {
            std::ifstream fileStream(file.data());
            std::string fileString((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

            assert(!fileString.empty() and "Shader::OpenFile: Unable to open/read file provided.");

            return fileString;
        }

        bool CheckCompileStatus(unsigned int id)
        {
            int status;
            char info[512];

            glGetShaderiv(id, GL_COMPILE_STATUS, &status);
            glGetShaderInfoLog(id, 512, NULL, info);

            assert(status != GL_FALSE and info);

            return status;
        }

        bool CheckLinkingStatus(unsigned int id)
        {
            int status;
            char info[512];

            glGetProgramiv(id, GL_LINK_STATUS, &status);
            glGetProgramInfoLog(id, 512, NULL, info);

            assert(status != GL_FALSE and info);

            return status;
        }
    };

}