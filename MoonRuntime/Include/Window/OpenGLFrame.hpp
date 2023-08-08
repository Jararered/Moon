#pragma once

#include <glad/gl.h>
#include <glfw/glfw3.h>

class OpenGLFrame
{
public:
    OpenGLFrame() = default;
    ~OpenGLFrame() = default;

    void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_ID); }
    void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void Generate() { glGenFramebuffers(1, &m_ID); }

private:
    unsigned int m_ID;
};