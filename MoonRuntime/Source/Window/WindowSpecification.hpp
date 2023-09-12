#pragma once

#include <string>

struct WindowSpecification
{
    std::string Title = "Title";
    float Width = 1280;
    float Height = 720;
    bool VSync = true;
};