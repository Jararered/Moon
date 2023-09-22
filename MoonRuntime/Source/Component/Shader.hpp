#pragma once

#include <fstream>
#include <glad/gl.h>
#include <print>
#include <string>

struct Shader
{
    unsigned int ID = 0;

    Shader() = default;
    Shader(std::string_view vertexPath, std::string_view fragmentPath)
    {
        int success;
        char info[512];

        // Vertex Shader
        unsigned int vertexID;
        std::ifstream vertexFile(vertexPath.data());
        std::string vertexString((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
        const char* vertexChar = vertexString.c_str();
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexID, 1, &vertexChar, NULL);
        glCompileShader(vertexID);
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
        if (not success)
        {
            glDeleteShader(vertexID);
            glGetShaderInfoLog(vertexID, 512, NULL, info);
            std::println("Compilation failed: {}", std::string(info));
        }

        // Fragment Shader
        unsigned int fragmentID;
        std::ifstream fragmentFile(fragmentPath.data());
        std::string fragmentString((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
        const char* fragmentChar = fragmentString.c_str();
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentID, 1, &fragmentChar, NULL);
        glCompileShader(fragmentID);
        glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
        if (not success)
        {
            glGetShaderInfoLog(fragmentID, 512, NULL, info);
            glDeleteShader(fragmentID);
            std::println("Compilation failed: {}", std::string(info));
        }

        // Linking
        unsigned int shaderID;
        shaderID = glCreateProgram();
        glAttachShader(shaderID, vertexID);
        glAttachShader(shaderID, fragmentID);
        glLinkProgram(shaderID);
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (not success)
        {
            glDeleteProgram(shaderID);
            glGetProgramInfoLog(shaderID, 512, NULL, info);
            std::println("Linking failed: {}", std::string(info));
        }

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

        std::println("Shader: {}", shaderID);
        ID = shaderID;
    }
};