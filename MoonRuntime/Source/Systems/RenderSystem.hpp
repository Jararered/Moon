#pragma once

#include "Entity.hpp"
#include "System.hpp"

class RenderSystem : public System
{
public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    Entity m_CameraEntity;

    unsigned int m_CurrentShader = 0;
    unsigned int m_CurrentTexture = 0;

    float m_NearClip;
    float m_FarClip;

    void PollDebugControls();
};