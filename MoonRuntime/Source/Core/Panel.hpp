#pragma once

#include <imgui.h>

class Panel
{
public:
    virtual ~Panel() = default;

    virtual void Update() = 0;
};