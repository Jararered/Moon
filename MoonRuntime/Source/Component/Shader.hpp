#pragma once

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
        CheckCompileStatus(vertexID);

        // Fragment Shader
        auto fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        auto fragmentSource = OpenFile(fragmentPath);
        auto fragmentSourceChar = fragmentSource.c_str();
        glShaderSource(fragmentID, 1, &fragmentSourceChar, NULL);
        glCompileShader(fragmentID);
        CheckCompileStatus(fragmentID);

        // Linking
        auto shaderID = glCreateProgram();
        glAttachShader(shaderID, vertexID);
        glAttachShader(shaderID, fragmentID);
        glLinkProgram(shaderID);
        CheckLinkingStatus(shaderID);

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

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
        CheckCompileStatus(vertexID);

        // Geometry Shader
        auto geometryID = glCreateShader(GL_GEOMETRY_SHADER);
        auto geometrySource = OpenFile(geometryPath);
        auto geometrySourceChar = geometrySource.c_str();
        glShaderSource(geometryID, 1, &geometrySourceChar, NULL);
        glCompileShader(geometryID);
        CheckCompileStatus(geometryID);

        // Fragment Shader
        auto fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        auto fragmentSource = OpenFile(fragmentPath);
        auto fragmentSourceChar = fragmentSource.c_str();
        glShaderSource(fragmentID, 1, &fragmentSourceChar, NULL);
        glCompileShader(fragmentID);
        CheckCompileStatus(fragmentID);

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

        ID = shaderID;
    }

    std::string OpenFile(std::string_view file)
    {
        std::ifstream fileStream(file.data());
        std::string fileString((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        return fileString;
    }

    void CheckCompileStatus(unsigned int id)
    {
        int success;
        char info[512];

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (not success)
        {
            glGetShaderInfoLog(id, 512, NULL, info);
            std::cout << "Shader::CheckCompileStatus(): " << info << "\n";
            glDeleteShader(id);
        }
    }

    void CheckLinkingStatus(unsigned int id)
    {
        int success;
        char info[512];

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (not success)
        {
            glGetProgramInfoLog(id, 512, NULL, info);
            std::cout << "Shader::CheckLinkingStatus(): " << info << "\n";
            glDeleteProgram(id);
        }
    }
};