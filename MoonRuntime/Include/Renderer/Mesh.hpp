#pragma once

#include "VertexBuffer.hpp"
#include "Shader.hpp"

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Mesh
{
public:
    Mesh() = default;
    virtual ~Mesh() = default;

    void UseShader() { m_Shader.Bind(); }
    void Draw()
    {
        m_VertexBuffer.Bind();
        m_VertexBuffer.Draw();
        m_VertexBuffer.Unbind();
    }

protected:
    Shader m_Shader;
    VertexBuffer m_VertexBuffer;

    glm::mat4 m_TranslationMatrix = glm::mat4(1.0f);
    glm::mat4 m_RotationMatrix = glm::mat4(1.0f);

public:
    Shader& GetShader() { return m_Shader; }
    void SetShader(const Shader& shader) { m_Shader = shader; }

    VertexBuffer GetVertexBuffer() const { return m_VertexBuffer; }
    void SetVertexBuffer(const VertexBuffer& vertexBuffer) { m_VertexBuffer = vertexBuffer; }

    glm::mat4& GetTranslationMatrix() { return m_TranslationMatrix; }
    void SetTranslationMatrix(const glm::mat4& matrix) { m_TranslationMatrix = matrix; };

    glm::mat4& GetRotationMatrix() { return m_RotationMatrix; }
    void SetRotationMatrix(const glm::mat4& matrix) { m_RotationMatrix = matrix; }
};