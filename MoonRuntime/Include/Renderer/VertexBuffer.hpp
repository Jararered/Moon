#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <iostream>

struct Vertex
{
    Vertex(glm::vec3 position);
    Vertex(glm::vec3 position, glm::vec3 color);
    Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal);

    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Normal;
};

class VertexBuffer
{
public:
    VertexBuffer() = default;
    ~VertexBuffer() = default;

    void Generate();
    void Delete();
    void Bind();
    void Unbind();
    void Draw();
    void UpdateGeometry();

    void SetVertices(const std::vector<Vertex>& verticies) { m_Vertices = verticies; }
    std::vector<Vertex>& GetVertices() { return m_Vertices; }

    void SetIndices(const std::vector<unsigned int>& indices) { m_Indices = indices; }
    std::vector<unsigned int>& GetIndices() { return m_Indices; }

private:
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_IBO = 0;

    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
};