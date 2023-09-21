#pragma once

#include "Component/Mesh.hpp"
#include "Component/Shader.hpp"
#include "Framebuffer.hpp"
#include "System.hpp"

#include <glm/mat4x4.hpp>

class RenderSystem final : public System
{
public:
    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem(RenderSystem&&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;
    RenderSystem& operator=(RenderSystem&&) = delete;
    ~RenderSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

public:
    void SetMatrix(int id, const std::string& location, const glm::mat4& matrix) { glUniformMatrix4fv(glGetUniformLocation(id, location.c_str()), 1, GL_FALSE, (float*)&matrix); }

private:
    int m_Width = 0;
    int m_Height = 0;

    void PollDebugControls();

    Entity m_Camera;
    MSAAFramebuffer m_Framebuffer;
};