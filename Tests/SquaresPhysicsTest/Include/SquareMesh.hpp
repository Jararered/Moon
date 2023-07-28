#pragma once

#include <Mesh.hpp>

class SquareMesh : public Mesh
{
public:
    SquareMesh(float size = 1.0f, const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0, 1, 2, 2, 3, 0 });
        m_Geometry.Vertices.emplace_back(glm::vec3{ +size / 2.0f, -size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_Geometry.Vertices.emplace_back(glm::vec3{ +size / 2.0f, +size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_Geometry.Vertices.emplace_back(glm::vec3{ -size / 2.0f, +size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_Geometry.Vertices.emplace_back(glm::vec3{ -size / 2.0f, -size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });

        Generate();
    }
};