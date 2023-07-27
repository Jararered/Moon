#pragma once

#include "Input.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
    Camera() = default;
    virtual ~Camera() = default;

    virtual void Update(float dt) {};
    virtual void Attach(Shader* shader) { p_Shader = shader; }

public:
    Shader* GetShader() const { return p_Shader; }
    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetDirection() const { return m_Direction; }
    glm::vec3 GetRight() const { return m_Right; }
    glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
    glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

    // float* GetViewMatrixPtr() const { return &m_ViewMatrix[0][0]; }
    // float* GetProjectionMatrixPtr() const { return &m_ProjectionMatrix[0][0]; }

protected:
    Shader* p_Shader = nullptr;
    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Direction = { 0.0f, 0.0f, -1.0f };
    glm::vec3 m_Right = glm::cross(m_Direction, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
    glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);
};