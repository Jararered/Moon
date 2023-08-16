#pragma once

#include <glad/gl.h>
#include <iostream>
#include <vector>

template <class VertexType> class VertexBuffer
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

        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(VertexType), (void*)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(VertexType), m_Vertices.data());

        glGenBuffers(1, &m_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), (void*)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(unsigned int), m_Indices.data());

        VertexType::EnableVertexAttributes();

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        std::cout << "Generated: VAO " << m_VAO << ", VBO " << m_VBO << ", IBO " << m_IBO << "\n";
    }

    void Delete()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_IBO);
    }

    void Bind() { glBindVertexArray(m_VAO); }

    void Unbind() { glBindVertexArray(0); }

    void Draw() { glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0); }

    void UpdateGeometry()
    {
        // Binding
        glBindVertexArray(m_VAO);

        // Bind buffers
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

        // Send data to buffers
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(VertexType), m_Vertices.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(unsigned int), m_Indices.data());

        // Unbind Buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

private:
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_IBO = 0;

    std::vector<VertexType> m_Vertices;
    std::vector<unsigned int> m_Indices;

public:
    inline std::vector<VertexType>& GetVertices() { return m_Vertices; }
    inline std::vector<unsigned int>& GetIndices() { return m_Indices; }
};