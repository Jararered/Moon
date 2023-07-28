#pragma once

#include "Geometry.hpp"
#include "Shader.hpp"
// #include "Camera.hpp"

#include <glad/gl.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Mesh
{
public:
    Mesh() = default;
    Mesh(Geometry geometry);
    virtual ~Mesh();

    void Bind();
    void Unbind();
    void Draw();

    void UpdateGeometry();

    Geometry& GetGeometry() { return m_Geometry; }
    void SetGeometry(const Geometry& geometry);

    Shader& GetShader() { return m_Shader; }
    void SetShader(const Shader& shader) { m_Shader = shader; }

    glm::mat4& GetTranslationMatrix() { return m_TranslationMatrix; }
    void SetTranslationMatrix(const glm::mat4& matrix);

    glm::mat4& GetRotationMatrix() { return m_RotationMatrix; }
    void SetRotationMatrix(const glm::mat4& matrix);

protected:
    void Generate();

    Geometry m_Geometry;
    Shader m_Shader;
    glm::mat4 m_TranslationMatrix = glm::mat4(1.0f);
    glm::mat4 m_RotationMatrix = glm::mat4(1.0f);

private:
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_IBO = 0;
};