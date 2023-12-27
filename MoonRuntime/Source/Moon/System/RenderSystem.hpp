#pragma once

#include "Components.hpp"
#include "Framebuffer.hpp"
#include "Scenario/Scenario.hpp"
#include "Scenario/SystemInterface.hpp"

#include <glm/mat4x4.hpp>

namespace Moon
{

    class RenderSystem final : public SystemInterface
    {
    public:
        RenderSystem() = default;
        ~RenderSystem() override = default;

    public:
        void Register(std::shared_ptr<Scenario> scenario) override;
        void Initialize() override;
        void Update(float dt) override;
        void Finalize() override;

    private:
        void ConfigureFramebuffer(int width, int height);
        void ConfigureCallbacks();

    private:
        int m_Width = 0;
        int m_Height = 0;

        float m_NearClip;
        float m_FarClip;

        int m_PolygonMode;

        Entity m_Camera;
        MSAAFramebuffer m_Framebuffer;
        Framebuffer m_WireFramebuffer;
    };

}