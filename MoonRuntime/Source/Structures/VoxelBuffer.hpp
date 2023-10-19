#pragma once

#include "BufferInterface.hpp"
#include "Voxel.hpp"

#include <glad/gl.h>
#include <vector>

class VoxelBuffer : public BufferInterface
{
public:
    VoxelBuffer() = default;
    ~VoxelBuffer() override = default;

    void BufferData() override
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, m_Data.size() * sizeof(Voxel), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Data.size() * sizeof(Voxel), m_Data.data());

        glVertexAttribPointer(0, sizeof(Voxel) / sizeof(float), GL_FLOAT, 0, sizeof(Voxel), nullptr);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Delete() override
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void Bind() override { glBindVertexArray(m_VAO); }

    void Unbind() override { glBindVertexArray(0); }

    void Draw() override { glDrawArrays(GL_POINTS, 0, m_Data.size()); }

    void Update() override
    {
        // Binding
        glBindVertexArray(m_VAO);

        // Bind buffers
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Send data to buffers
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Data.size() * sizeof(Voxel), m_Data.data());

        // Unbind Buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

public:
    [[nodiscard]] inline std::vector<Voxel>& GetData() { return m_Data; }

private:
    std::vector<Voxel> m_Data;
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
};