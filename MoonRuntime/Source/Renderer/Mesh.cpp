#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(Geometry geometry)
    : m_Geometry(geometry)
{
    Generate();
}

Mesh::~Mesh()
{
    std::cout << "Deleting VAO: " << m_VAO << "\n";
    glDeleteVertexArrays(1, &m_VAO);

    std::cout << "Deleting VBO: " << m_VBO << "\n";
    glDeleteBuffers(1, &m_VBO);

    std::cout << "Deleting IBO: " << m_IBO << "\n";
    glDeleteBuffers(1, &m_IBO);

    std::cout << "Mesh::~Mesh()" << "\n";
}

void Mesh::Bind()
{
    m_Shader.Bind();
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind()
{
    glBindVertexArray(0);
}

void Mesh::SetGeometry(const Geometry& geometry)
{
    m_Geometry = geometry;
    Generate();
}

void Mesh::SetTranslationMatrix(const glm::mat4& matrix)
{
    m_TranslationMatrix = matrix;
}

void Mesh::SetRotationMatrix(const glm::mat4& matrix)
{
    m_RotationMatrix = matrix;
}

void Mesh::Generate()
{
    // Generate buffers on the GPU
    glGenVertexArrays(1, &m_VAO);
    std::cout << "Created VAO: " << m_VAO << "\n";

    // Bind the VAO
    glBindVertexArray(m_VAO);

    // Bind the VBO and send vertex data over
    {
        // Size in bytes
        size_t bytes = m_Geometry.Vertices.size() * sizeof(Vertex);

        glGenBuffers(1, &m_VBO);
        std::cout << "Created VBO: " << m_VBO << "\n";

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, bytes, (void*)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, bytes, m_Geometry.Vertices.data());
    }

    // Bind the IBO and send index data over
    {
        // Size in bytes
        size_t bytes = m_Geometry.Indices.size() * sizeof(unsigned int);

        glGenBuffers(1, &m_IBO);
        std::cout << "Created IBO: " << m_IBO << "\n";

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, (void*)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bytes, m_Geometry.Indices.data());
    }

    // Configuring the VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Color)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(2);

    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::UpdateGeometry()
{
    // Binding
    glBindVertexArray(m_VAO);

    {
        // Bind buffers
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

        // Send data to buffers
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Geometry.Vertices.size() * sizeof(Vertex), m_Geometry.Vertices.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Geometry.Indices.size() * sizeof(unsigned int), m_Geometry.Indices.data());

        // Unbind Buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
}

void Mesh::Draw()
{
    m_Shader.Bind();
    glDrawElements(GL_TRIANGLES, m_Geometry.Indices.size(), GL_UNSIGNED_INT, 0);
    m_Shader.Unbind();
}

