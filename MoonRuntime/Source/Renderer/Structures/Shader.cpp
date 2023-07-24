#include "Shader.hpp"

#include <glad/gl.h>
#include <fstream>
#include <iostream>

Shader::Shader()
{
    std::cout << "Shader::Shader()" << "\n";
}

Shader::~Shader()
{
    std::cout << "Shader::~Shader()" << "\n";
}

void Shader::Compile(const char *vertFile, const char *fragFile)
{
    ID = glCreateProgram();

    unsigned int vertexID, fragmentID;
    int successvert;
    int successfrag;
    int successlink;
    char infoLog[512];

    // Vertex Shader
    {
        std::ifstream file(vertFile);
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << contents << std::endl;
        const char *contentsChar = contents.c_str();
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexID, 1, &contentsChar, NULL);
        glCompileShader(vertexID);
    }

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &successvert);
    if (!successvert)
    {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << "\n";
    }

    // Fragment Shader
    {
        std::ifstream file(fragFile);
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << contents << std::endl;
        const char *contentsChar = contents.c_str();
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentID, 1, &contentsChar, NULL);
        glCompileShader(fragmentID);
    }

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &successfrag);
    if (!successfrag)
    {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << "\n";
    }

    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &successlink);
    if (!successlink)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << "\n";
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    if (successvert && successfrag && successlink)
    {
        std::cout << "Created shader: " << ID << "\n";
    }
}

void Shader::Delete()
{
    std::cout << "Deleting shader: " << ID << "\n";
    glDeleteProgram(ID);
}

void Shader::Bind()
{
    glUseProgram(ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}