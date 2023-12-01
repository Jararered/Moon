#pragma once

#include <assert.h>
#include <fstream>
#include <glad/gl.h>
#include <iostream>
#include <string>

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