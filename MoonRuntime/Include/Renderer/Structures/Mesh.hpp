#pragma once

#include <glad/gl.h>
#include <vector>

#include "Geometry.hpp"
#include "Camera.hpp"

class Mesh
{
public:
    Mesh(Geometry geometry);
    ~Mesh();

    void Bind();
    void Unbind();

    void Update(float dt);
    void UpdateGeometry();

    void Draw();

private:
    Geometry m_Geometry;

    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_IBO = 0;

public:
    Geometry& GetGeometry() { return m_Geometry; }
};