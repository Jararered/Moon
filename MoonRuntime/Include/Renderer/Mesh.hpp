#pragma once

#include "VertexBuffer.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class MeshBase
{
public:
    MeshBase() = default;
    virtual ~MeshBase() = default;

    virtual void Bind() {};
    virtual void Draw() {};
    virtual void Unbind() {};

protected:
    Shader m_Shader;
    Texture m_Texture;

    glm::mat4 m_TranslationMatrix = glm::mat4(1.0f);
    glm::mat4 m_RotationMatrix = glm::mat4(1.0f);

public:
    Shader& GetShader() { return m_Shader; }
    void SetShader(const Shader& shader) { m_Shader = shader; }

    glm::mat4& GetTranslationMatrix() { return m_TranslationMatrix; }
    void SetTranslationMatrix(const glm::mat4& matrix) { m_TranslationMatrix = matrix; };

    glm::mat4& GetRotationMatrix() { return m_RotationMatrix; }
    void SetRotationMatrix(const glm::mat4& matrix) { m_RotationMatrix = matrix; }

    Texture GetTexture() const { return m_Texture; }
    void SetTexture(const Texture& texture) { m_Texture = texture; }
};

template <typename VertexType>
class Mesh : public MeshBase
{
public:
    Mesh<VertexType>() = default;
    virtual ~Mesh<VertexType>() override = default;

protected:
    VertexBuffer<VertexType> m_VertexBuffer;

public:
    VertexBuffer<VertexType> GetVertexBuffer() const { return m_VertexBuffer; }
    void SetVertexBuffer(const VertexBuffer<VertexType>& vertexBuffer) { m_VertexBuffer = vertexBuffer; }

    void AddToVertexBuffer(const VertexType& vertex) { m_VertexBuffer.GetVertices().emplace_back(vertex); }
    // void AddToVertexBuffer(const VertexType&& vertex) { m_VertexBuffer.GetVertices().emplace_back(vertex); }

    void Draw() override
    {
        Bind();
        m_VertexBuffer.Draw();
        Unbind();
    }

    void Bind() override
    {
        m_Shader.Bind();
        m_Texture.Bind();
        m_VertexBuffer.Bind();
    }

    void Unbind() override
    {
        m_Shader.Unbind();
        m_Texture.Unbind();
        m_VertexBuffer.Unbind();
    }
};