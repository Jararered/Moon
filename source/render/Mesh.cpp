#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(Geometry geometry, Shader shader)
    : m_Geometry(geometry), m_Shader(shader)
{
    // Generate buffers on the GPU
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);

    // Bind the VAO
    glBindVertexArray(m_VAO);

    // Bind the VBO and send vertex data over
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * m_Geometry.Vertices.size() * sizeof(Vertex), (void *)0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Geometry.Vertices.size() * sizeof(Vertex), m_Geometry.Vertices.data());

    // Bind the IBO and send index data over
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * m_Geometry.Indices.size() * sizeof(unsigned int), (void *)0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Geometry.Indices.size() * sizeof(unsigned int), m_Geometry.Indices.data());

    // Configuring the VAO for Positions, Texture Coordinates, and Normals
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Color)));

    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
    std::cout << "Deleting VAO: " << m_VAO << std::endl;
    glDeleteVertexArrays(1, &m_VAO);

    std::cout << "Deleting VBO: " << m_VBO << std::endl;
    glDeleteBuffers(1, &m_VBO);

    std::cout << "Deleting IBO: " << m_IBO << std::endl;
    glDeleteBuffers(1, &m_IBO);

    std::cout << "Mesh::~Mesh()" << std::endl;
}

void Mesh::Bind()
{
    glUseProgram(m_Shader.GetID());
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind()
{
    glUseProgram(0);
    glBindVertexArray(0);
}

void Mesh::Update()
{
}

void Mesh::UpdateGeometry()
{
    // Binding
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    // Buffer geometry data
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Geometry.Vertices.size() * sizeof(Vertex), m_Geometry.Vertices.data());
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Geometry.Indices.size() * sizeof(unsigned int), m_Geometry.Indices.data());

    // Unbinding everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}