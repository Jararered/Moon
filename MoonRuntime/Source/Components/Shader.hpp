#pragma once

#include <fstream>
#include <string>

struct Shader
{
    unsigned int ID = 0;

    static unsigned int CreateShader(const std::string& vertexFile, const std::string& fragmentFile)
    {
        // Vertex Shader
        unsigned int vertexID;
        {
            std::ifstream file(vertexFile);
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            const char* contentsChar = contents.c_str();
            vertexID = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexID, 1, &contentsChar, NULL);
            glCompileShader(vertexID);
        }

        int successVert;
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &successVert);
        if (!successVert)
        {
            glDeleteShader(vertexID);
            char infoLog[512];
            glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
            std::cout << "Shader::Compile(): Compilation failed: \n";
            std::cout << infoLog << "\n";
            return 0;
        }

        // Fragment Shader
        unsigned int fragmentID;
        {
            std::ifstream file(fragmentFile);
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            const char* contentsChar = contents.c_str();
            fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentID, 1, &contentsChar, NULL);
            glCompileShader(fragmentID);
        }

        int successFrag;
        glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &successFrag);
        if (!successFrag)
        {
            glDeleteShader(fragmentID);
            char infoLog[512];
            glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
            std::cout << "Shader::Compile(): Compilation failed: \n";
            std::cout << infoLog << "\n";
            return 0;
        }

        unsigned int id = glCreateProgram();
        glAttachShader(id, vertexID);
        glAttachShader(id, fragmentID);

        int successLink;
        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &successLink);
        if (!successLink)
        {
            glDeleteProgram(id);
            char infoLog[512];
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "Shader::Compile(): Linking failed: \n";
            std::cout << infoLog << "\n";
        }

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

        if (successVert && successFrag && successLink)
        {
            std::cout << "Shader::Compile(): Created shader: " << id << "\n";
        }
        return id;
    }
};