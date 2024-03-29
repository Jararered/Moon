#pragma once

#include "Signature.hpp"
#include "UUID.hpp"

#include <memory>
#include <set>
#include <string>

namespace Moon
{

    class Scenario;

    class SystemInterface
    {
    public:
        SystemInterface() = default;
        virtual ~SystemInterface() = default;

    public:
        virtual void Register(std::shared_ptr<Scenario> scenario) = 0;

        virtual void Initialize() = 0;
        virtual void Update(float dt) = 0;
        virtual void Finalize() = 0;

        std::set<UUID> m_Entities;
        std::shared_ptr<Scenario> m_Scenario;
    };

}