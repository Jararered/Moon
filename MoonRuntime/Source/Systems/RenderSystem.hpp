#pragma once

#include "Component/Mesh.hpp"
#include "Component/Shader.hpp"
#include "Framebuffer.hpp"
#include "System.hpp"

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

private:
    int m_Width = 0;
    int m_Height = 0;

    void PollDebugControls();

    Entity m_Camera;
    MSAAFramebuffer m_Framebuffer;
};