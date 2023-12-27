#pragma once

#include "Core/Scenario/Scenario.hpp"
#include "Core/Scenario/SystemInterface.hpp"

#include "Core/Components.hpp"

#include <glm/vec3.hpp>

namespace Moon
{

    class PhysicsSystem final : public SystemInterface
    {
    public:
        PhysicsSystem() = default;
        ~PhysicsSystem() override = default;

    public:
        void Register(std::shared_ptr<Scenario> scenario) override;
        void Initialize() override;
        void Update(float dt) override;
        void Finalize() override;

    private:
        [[nodiscard]] bool IsIntersect(const Transform& transform1, const Transform& transform2);

        void UpdateStep(float dt, UUID entity);
        void UpdateCollision(UUID entity);
        void UpdateFriction(float dt, UUID entity);

        int m_SubStepCount;
        float m_AirFrictionCoefficient;   // Velocity lost due to movement through air
        float m_SolidFrictionCoefficient; // Velocity lost due to physical collision
        glm::vec3 m_Gravity;              // Acceleration downwards
    };

}