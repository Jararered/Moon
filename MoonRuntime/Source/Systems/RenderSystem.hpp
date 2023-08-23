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

    float m_NearClip;
    float m_FarClip;

    void PollDebugControls();
    void EnableWireframes();
    void DisableWireframes();
    void EnableBackCulling();
    void DisableBackCulling();
};