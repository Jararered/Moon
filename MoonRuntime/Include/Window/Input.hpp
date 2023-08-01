#pragma once

#include "KeyboardKeyCodes.hpp"
#include "MouseButtonCodes.hpp"

#include <glm/vec2.hpp>

namespace Input
{
    // Keyboard related functions
    static bool IsKeyPressed(int keycode);

    // Mouse button related functions
    static bool IsMouseButtonPressed(int mouseButtonCode);

    static bool IsLeftClick();

    static bool IsRightClick();

    // Mouse position functions
    static glm::vec2 GetMousePosition();

    // Mouse handling functions
    static bool IsMouseCaptured();

    static glm::vec2 GetMouseMovement();

    static void CaptureCursor();

    static void ReleaseCursor();

    // Updates the current state of all inputs
    static void PollEvents();
};
