#pragma once

#include <string>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    void Compile(const char* vertFile, const char* fragFile);

    const void Bind() const;
    void Unbind();
    void Delete();

    unsigned int ID = 0;
};