#pragma once

#include <Core/Panel.hpp>

class CreateEntityPanel final : public Panel
{
public:
    ~CreateEntityPanel() override = default;

    void Update() override;
};
