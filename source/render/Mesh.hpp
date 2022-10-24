#pragma once

#include <glad/gl.h>
#include <vector>

#include "Geometry.hpp"
#include "Shader.hpp"

class Mesh
{
public:
    Mesh(Geometry geometry, Shader shader);
    ~Mesh();

    void Bind();
    void Unbind();

    void Update();
    void UpdateGeometry();

private:
    Geometry m_Geometry;
    Shader m_Shader;

    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_IBO = 0;

public:
    Geometry &GetGeometry() { return m_Geometry; }
    Shader &GetShader() { return m_Shader; }
};