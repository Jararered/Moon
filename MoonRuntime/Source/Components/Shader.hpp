#pragma once

#include <fstream>
#include <glad/gl.h>
#include <print>
#include <string>

struct Shader
{
    unsigned int ID = 0;

    static unsigned int CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        int success;
        char info[512];

        // Vertex Shader
        unsigned int vertexID;
        std::ifstream vertexFile(vertexPath);
        std::string vertexString((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
        const char* vertexChar = vertexString.c_str();
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexID, 1, &vertexChar, NULL);
        glCompileShader(vertexID);
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glDeleteShader(vertexID);
            glGetShaderInfoLog(vertexID, 512, NULL, info);
            std::println("Compilation failed: {}", std::string(info));
            return 0;
        }

        // Fragment Shader
        unsigned int fragmentID;
        std::ifstream fragmentFile(fragmentPath);
        std::string fragmentString((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
        const char* fragmentChar = fragmentString.c_str();
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentID, 1, &fragmentChar, NULL);
        glCompileShader(fragmentID);
        glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentID, 512, NULL, info);
            glDeleteShader(fragmentID);
            std::println("Compilation failed: {}", std::string(info));
            return 0;
        }

        // Linking
        unsigned int shaderID;
        shaderID = glCreateProgram();
        glAttachShader(shaderID, vertexID);
        glAttachShader(shaderID, fragmentID);
        glLinkProgram(shaderID);
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glDeleteProgram(shaderID);
            glGetProgramInfoLog(shaderID, 512, NULL, info);
            std::println("Linking failed: {}", std::string(info));
            return 0;
        }

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

        std::println("Created shader: {}", shaderID);
        return shaderID;
    }
};