#include "Shader.hpp"

#include <glad/gl.h>
#include <fstream>
#include <iostream>

void Shader::Compile(const char* vertFile, const char* fragFile)
{

    // Vertex Shader
    unsigned int vertexID;
    int successVert;
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
        char infoLog[512];
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cout << "Shader::Compile(): Compilation failed: \n";
        std::cout << infoLog << "\n";
        return;
    }

    // Fragment Shader
    unsigned int fragmentID;
    int successFrag;
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
        char infoLog[512];
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cout << "Shader::Compile(): Compilation failed: \n";
        std::cout << infoLog << "\n";
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexID);
    glAttachShader(m_ID, fragmentID);

    int successLink;
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &successLink);
    if (!successLink)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "Shader::Compile(): Linking failed: \n";
        std::cout << infoLog << "\n";
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    if (successVert && successFrag && successLink)
    {
        std::cout << "Shader::Compile(): Created shader: " << m_ID << "\n";
    }
}

void Shader::Delete()
{
    std::cout << "Shader::Delete(): Deleting shader: " << m_ID << "\n";
    glDeleteProgram(m_ID);
}

void Shader::Bind()
{
    glUseProgram(m_ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetMatrix(const std::string& uniform, const glm::mat2& matrix) { glUniformMatrix2fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, GL_FALSE, (float*)&matrix); }
void Shader::SetMatrix(const std::string& uniform, const glm::mat3& matrix) { glUniformMatrix3fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, GL_FALSE, (float*)&matrix); }
void Shader::SetMatrix(const std::string& uniform, const glm::mat4& matrix) { glUniformMatrix4fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, GL_FALSE, (float*)&matrix); }
void Shader::SetVector(const std::string& uniform, const glm::vec2& vector) { glUniform2fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, (float*)&vector); }
void Shader::SetVector(const std::string& uniform, const glm::vec3& vector) { glUniform3fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, (float*)&vector); }
void Shader::SetVector(const std::string& uniform, const glm::vec4& vector) { glUniform4fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, (float*)&vector); }
void Shader::SetFloat(const std::string& uniform, const float& value) { glUniform1fv(glGetUniformLocation(m_ID, uniform.c_str()), 1, &value); }
