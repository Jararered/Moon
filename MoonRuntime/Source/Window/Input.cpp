#include "Input.hpp"

#include <glfw/glfw3.h>

namespace Input
{
    // Keyboard related functions
    bool IsKeyPressed(int keycode)
    {
        return glfwGetKey(glfwGetCurrentContext(), keycode) == GLFW_PRESS;
    }

    // Mouse button related functions
    bool IsMouseButtonPressed(int mouseButtonCode)
    {
        int state = glfwGetMouseButton(glfwGetCurrentContext(), mouseButtonCode);
        return state == GLFW_PRESS;
    }

    bool IsLeftClick()
    {
        int state = glfwGetMouseButton(glfwGetCurrentContext(), MOUSE_BUTTON_LEFT);
        return state == GLFW_PRESS;
    }

    bool IsRightClick()
    {
        int state = glfwGetMouseButton(glfwGetCurrentContext(), MOUSE_BUTTON_RIGHT);
        return state == GLFW_PRESS;
    }

    // Mouse position functions
    glm::vec2 GetMousePosition()
    {
        double xpos, ypos;
        glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
        return { static_cast<float>(xpos), static_cast<float>(-ypos) };
    }

    // Mouse handling functions
    bool IsMouseCaptured()
    {
        int option = glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR);
        return option == GLFW_CURSOR_DISABLED;
    }

    glm::vec2 GetMouseMovement()
    {
        if (IsMouseCaptured())
        {
            glm::vec2 mousepos = GetMousePosition();
            glfwSetCursorPos(glfwGetCurrentContext(), 0.0, 0.0);
            return mousepos;
        }
        return { 0.0f, 0.0f };
    }

    void CaptureCursor()
    {
        if (glfwRawMouseMotionSupported())
        {
            glfwSetInputMode(glfwGetCurrentContext(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Need to center cursor before cursor position callback is run
        // Prevents a possibly large xpos/ypos when entering the window
        glfwSetCursorPos(glfwGetCurrentContext(), 0.0, 0.0);
    }

    void ReleaseCursor()
    {
        glm::ivec2 size;
        glfwGetWindowSize(glfwGetCurrentContext(), &size.x, &size.y);
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(glfwGetCurrentContext(), static_cast<double>(size.x / 2), static_cast<double>(size.y / 2));
    }

    // Updates the current state of all inputs
    void PollEvents()
    {
        glfwPollEvents();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            Input::ReleaseCursor();
        }
    }
};