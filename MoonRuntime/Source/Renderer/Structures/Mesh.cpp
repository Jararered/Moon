#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(Geometry geometry, Shader shader)
    : m_Geometry(geometry), m_Shader(shader)
{
    // Generate buffers on the GPU
    glGenVertexArrays(1, &m_VAO);
    std::cout << "Created VAO: " << m_VAO << std::endl;

    // Bind the VAO
    glBindVertexArray(m_VAO);

    // Bind the VBO and send vertex data over
    {
        // Size in bytes
        size_t size = m_Geometry.Vertices.size() * sizeof(Vertex);

        glGenBuffers(1, &m_VBO);
        std::cout << "Created VBO: " << m_VBO << std::endl;

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, (void *)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_Geometry.Vertices.data());
    }

    // Bind the IBO and send index data over
    {
        // Size in bytes
        size_t size = m_Geometry.Indices.size() * sizeof(unsigned int);

        glGenBuffers(1, &m_IBO);
        std::cout << "Created IBO: " << m_IBO << std::endl;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (void *)0, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, m_Geometry.Indices.data());
    }

    // Configuring the VAO for Positions and Colors
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);

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
    // std::cout << "Binding shader: " << m_Shader.ID << std::endl;
    m_Shader.Bind();

    // std::cout << "Binding VAO: " << m_VAO << std::endl;
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind()
{
    // std::cout << "Unbinding shader: " << m_Shader.ID << std::endl;
    m_Shader.Unbind();

    // std::cout << "Unbinding VAO: " << m_Shader.ID << std::endl;
    glBindVertexArray(0);
}

void Mesh::Update(float dt)
{
    glUniform1f(glGetUniformLocation(m_Shader.ID, "u_Time"), dt);
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

void Mesh::Draw(Camera& camera)
{
    // Update uniform data
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.ID, "u_ViewMatrix"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_Shader.ID, "u_ProjectionMatrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);

    // Finally draw everything
    glDrawElements(GL_TRIANGLES, m_Geometry.Indices.size(), GL_UNSIGNED_INT, 0);
}