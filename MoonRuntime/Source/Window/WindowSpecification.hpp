#pragma once

#include <string>

struct WindowSpecification
{
    std::string Title = "Title";
    int Width = 1280;
    int Height = 720;
    bool VSync = true;
};