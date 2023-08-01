#pragma once

#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Mesh
{
public:
    Mesh() = default;
    virtual ~Mesh() = default;

    void Bind();
    void Unbind();

    void Draw();

protected:
    VertexBuffer m_VertexBuffer;
    Shader m_Shader;
    Texture m_Texture;

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

    Texture GetTexture() const { return m_Texture; }
    void SetTexture(const Texture& texture) { m_Texture = texture; }
};