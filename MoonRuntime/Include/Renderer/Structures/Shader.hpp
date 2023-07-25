#pragma once

#include <string>

struct Shader
{
    Shader();
    ~Shader();

    void Compile(const char *vertFile, const char *fragFile);
    void Compile(const std::string& vertFile, const std::string& fragFile);
    void Delete();
    void Bind();
    void Unbind();

    unsigned int ID = 0;
};