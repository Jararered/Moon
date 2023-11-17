#pragma once

#include "Core/SystemInterface.hpp"

namespace Moon
{

    class CameraSystem final : public SystemInterface
    {
    public:
        CameraSystem() = default;
        ~CameraSystem() override = default;

    public:
        void Register(std::shared_ptr<Scenario> scenario) override;

        void Initialize() override;
        void Update(float dt) override;
        void Finalize() override;

        void UpdatePerspective(UUID entity);

    private:
        float m_Sensitivity = 0.2f;
    };

}