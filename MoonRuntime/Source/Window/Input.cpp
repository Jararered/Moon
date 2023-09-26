#include "Input.hpp"

#include <glfw/glfw3.h>

bool Input::IsKeyPressed(int keycode)
{
    const auto state = glfwGetKey(glfwGetCurrentContext(), keycode);
    return state == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(int mouseButtonCode)
{
    const auto state = glfwGetMouseButton(glfwGetCurrentContext(), mouseButtonCode);
    return state == GLFW_PRESS;
}

bool Input::IsLeftClick()
{
    const auto state = glfwGetMouseButton(glfwGetCurrentContext(), Mouse::ButtonLeft);
    return state == GLFW_PRESS;
}

bool Input::IsRightClick()
{
    const auto state = glfwGetMouseButton(glfwGetCurrentContext(), Mouse::ButtonRight);
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
    auto position = glm::dvec2(0.0);
    glfwGetCursorPos(glfwGetCurrentContext(), &position.x, &position.y);
    return glm::vec2(static_cast<float>(position.x), static_cast<float>(-position.y));
}

bool Input::IsMouseCaptured()
{
    const auto option = glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR);
    return option == GLFW_CURSOR_DISABLED;
}

glm::vec2 Input::GetCapturedMouseMovement()
{
    // This is intended to be called per-frame
    if (not IsMouseCaptured())
        return glm::vec2(0.0f);

    const auto mousepos = GetMousePosition();
    glfwSetCursorPos(glfwGetCurrentContext(), 0.0, 0.0);
    return mousepos;
}

void Input::CaptureCursor()
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Need to center cursor before cursor position callback is run
    // Prevents a possibly large xPosition/yPosition when entering the window
    glfwSetCursorPos(glfwGetCurrentContext(), 0.0, 0.0);
}

void Input::ReleaseCursor()
{
    auto position = glm::ivec2(0);
    glfwGetWindowSize(glfwGetCurrentContext(), &position.x, &position.y);
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPos(glfwGetCurrentContext(), static_cast<double>(position.x / 2), static_cast<double>(position.y / 2));
}

void Input::PollEvents()
{
    glfwPollEvents();
}