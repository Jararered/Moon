#pragma once

#include "Component/Mesh.hpp"
#include "Component/Shader.hpp"
#include "Framebuffer.hpp"
#include "SystemInterface.hpp"

#include <glm/mat4x4.hpp>

class RenderSystem final : public SystemInterface
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

private:
    void PollDebugControls();
    void CreateFramebuffer(int width, int height);

private:
    int m_Width = 0;
    int m_Height = 0;

    float m_NearClip;
    float m_FarClip;

    Entity m_Camera;
    Framebuffer m_Framebuffer;
};