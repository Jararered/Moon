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

    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID = 0;
};