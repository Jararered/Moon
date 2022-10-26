#pragma once

struct Shader
{
    Shader();
    ~Shader();

    void Compile(const char *vertFile, const char *fragFile);
    void Delete();
    void Bind();
    void Unbind();

    unsigned int ID = 0;
};