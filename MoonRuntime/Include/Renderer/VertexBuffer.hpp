#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <iostream>

struct Vertex
{
    Vertex(glm::vec3 position) :Position(position) {}
    Vertex(glm::vec3 position, glm::vec3 color) :Position(position), Color(color) {}
    Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal) :Position(position), Color(color), Normal(normal) {}
    Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal, glm::vec2 textureCoordinate) : Position(position), Color(color), Normal(normal), TextureCoordinate(textureCoordinate) {}

    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Normal;
    glm::vec2 TextureCoordinate;
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