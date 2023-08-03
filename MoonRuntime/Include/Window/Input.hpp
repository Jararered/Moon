#pragma once

#include <glm/vec2.hpp>

#include "KeyboardKeyCodes.hpp"
#include "MouseButtonCodes.hpp"

namespace Input
{
    bool IsKeyPressed(int keycode);
    bool IsMouseButtonPressed(int mouseButtonCode);

    bool IsLeftClick();
    bool IsRightClick();

    glm::vec2 GetMousePosition();
    glm::vec2 GetCapturedMouseMovement();

    bool IsMouseCaptured();
    void CaptureCursor();
    void ReleaseCursor();

    void PollEvents();
};
