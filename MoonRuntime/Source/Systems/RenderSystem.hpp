#pragma once

#include "System.hpp"

class RenderSystem final : public System
{
public:
    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = default;
    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(const RenderSystem&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;
    ~RenderSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    Entity m_Camera;

    unsigned int m_CurrentShader = 0;
    unsigned int m_CurrentTexture = 0;

    void PollDebugControls();
};