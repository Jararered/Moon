#pragma once

#include <glm/vec2.hpp>

#include "KeyboardKeyCodes.hpp"
#include "MouseButtonCodes.hpp"

namespace Input
{
    [[nodiscard]] bool IsKeyPressed(int keycode);
    [[nodiscard]] bool IsMouseButtonPressed(int mouseButtonCode);

    [[nodiscard]] bool IsLeftClick();
    [[nodiscard]] bool IsRightClick();

    [[nodiscard]] glm::vec2 GetMousePosition();
    [[nodiscard]] glm::vec2 GetCapturedMouseMovement();

    [[nodiscard]] bool IsMouseCaptured();

    void CaptureCursor();
    void ReleaseCursor();

    void PollEvents();
};
