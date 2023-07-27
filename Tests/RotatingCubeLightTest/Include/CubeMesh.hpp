#pragma once

#include <Mesh.hpp>

class CubeMesh : public Mesh
{
public:
    CubeMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_Geometry.Indices.insert(m_Geometry.Indices.end(), {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
            });

        // Right +x
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));

        // Left -x
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));

        // Top +y
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));

        // Bottom -y
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));

        // Front +z
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));

        // Back -z
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));

        Generate();
    }
};