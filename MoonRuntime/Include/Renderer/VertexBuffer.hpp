#pragma once

#include <glm/vec3.hpp>
#include <glad/gl.h>
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

    void Generate()
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), (void*)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(Vertex), m_Vertices.data());

        glGenBuffers(1, &m_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), (void*)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(unsigned int), m_Indices.data());
        
        std::cout << "Generated: VAO " << m_VAO << ", VBO " << m_VBO << ", IBO " << m_IBO << "\n";

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Color)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Delete()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_IBO);
    }

    void Bind()
    {
        glBindVertexArray(m_VAO);
    }

    void Unbind()
    {
        glBindVertexArray(0);
    }

    void Draw()
    {
        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    }

    void UpdateGeometry()
    {
        // Binding
        glBindVertexArray(m_VAO);

        // Bind buffers
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

        // Send data to buffers
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(Vertex), m_Vertices.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(unsigned int), m_Indices.data());

        // Unbind Buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

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