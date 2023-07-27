#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    void Compile(const char* vertFile, const char* fragFile);

    void Bind();
    void Unbind();
    void Delete();

    void SetMatrix(const std::string& uniform, const glm::mat2& matrix);
    void SetMatrix(const std::string& uniform, const glm::mat3& matrix);
    void SetMatrix(const std::string& uniform, const glm::mat4& matrix);
    void SetVector(const std::string& uniform, const glm::vec2& vector);
    void SetVector(const std::string& uniform, const glm::vec3& vector);
    void SetVector(const std::string& uniform, const glm::vec4& vector);
    void SetFloat(const std::string& uniform, const float& value);

    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID = 0;
};