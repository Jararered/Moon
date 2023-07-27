#include "Shader.hpp"

#include <glad/gl.h>
#include <fstream>
#include <iostream>

void Shader::Compile(const char* vertFile, const char* fragFile)
{
    m_ID = glCreateProgram();

    unsigned int vertexID, fragmentID;
    char infoLog[512];

    int successVert;
    // Vertex Shader
    {
        std::ifstream file(vertFile);
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        const char* contentsChar = contents.c_str();
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexID, 1, &contentsChar, NULL);
        glCompileShader(vertexID);
    }

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &successVert);
    if (!successVert)
    {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << infoLog << "\n";
    }

    int successFrag;
    // Fragment Shader
    {
        std::ifstream file(fragFile);
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        const char* contentsChar = contents.c_str();
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentID, 1, &contentsChar, NULL);
        glCompileShader(fragmentID);
    }

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &successFrag);
    if (!successFrag)
    {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << infoLog << "\n";
    }

    glAttachShader(m_ID, vertexID);
    glAttachShader(m_ID, fragmentID);
    glLinkProgram(m_ID);

    int successLink;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &successLink);
    if (!successLink)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
            << infoLog << "\n";
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    if (successVert && successFrag && successLink)
    {
        std::cout << "Created shader: " << m_ID << "\n";
    }
}

void Shader::Delete()
{
    std::cout << "Deleting shader: " << m_ID << "\n";
    glDeleteProgram(m_ID);
}

const void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}