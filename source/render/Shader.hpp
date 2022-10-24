#pragma once

class Shader
{
public:
    Shader();
    ~Shader();

    void Compile(const char *vertFile, const char *fragFile);
    void Bind();
    void Unbind();

private:
    unsigned int m_ID = 0;

public:
    unsigned int ID()
    {
        return m_ID;
    }
};