#pragma once

#include "Entity.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <print>

class Framebuffer final
{
public:
    Framebuffer() = default;
    ~Framebuffer() = default;

    void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); }
    void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void Draw()
    {
        // Draw 2D Frame Quad
        glDisable(GL_DEPTH_TEST);

        glUseProgram(m_FrameShader.ID);
        glBindTexture(GL_TEXTURE_2D, m_TBO);

        m_FrameMesh.Draw();
    }

    void Create(int width, int height)
    {
        if (m_FrameShader.ID == 0)
            m_FrameShader = Shader("Shaders/PositionTexture.vert", "Shaders/PositionTexture.frag");

        // Delete previous buffers if they exist
        if (m_FBO != 0)
            glDeleteFramebuffers(1, &m_FBO);
        if (m_TBO != 0)
            glDeleteTextures(1, &m_TBO);
        if (m_RBO != 0)
            glDeleteRenderbuffers(1, &m_RBO);

        // Create m_FBO
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // Create texture
        glGenTextures(1, &m_TBO);
        glBindTexture(GL_TEXTURE_2D, m_TBO);

        // Configure texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TBO, 0);

        // Create renderbuffer
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);

        // Configure renderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        // Check if the m_FBO was made successfully
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::println("Framebuffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        std::println("Created FBO: {}, TBO: {}, RBO: {}", m_FBO, m_TBO, m_RBO);
    }

    void Delete()
    {
        glDeleteFramebuffers(1, &m_FBO);
        glDeleteTextures(1, &m_TBO);
        glDeleteRenderbuffers(1, &m_RBO);
        std::println("Deleted FBO: {}, TBO: {}, RBO: {}", m_FBO, m_TBO, m_RBO);
    }

private:
    unsigned int m_FBO;
    unsigned int m_TBO;
    unsigned int m_RBO;

    class Frame : public MeshTemplate<Vertex2D<glm::vec2, glm::vec2>> // Position, Texture
    {
    public:
        Frame()
        {
            using Vertex = Vertex2D<glm::vec2, glm::vec2>;

            auto& vertices = VertexBuffer.GetVertices();
            vertices.reserve(4);
            vertices.emplace_back(Vertex({+1.0f, -1.0f}, {1.0f, 0.0f}));
            vertices.emplace_back(Vertex({+1.0f, +1.0f}, {1.0f, 1.0f}));
            vertices.emplace_back(Vertex({-1.0f, +1.0f}, {0.0f, 1.0f}));
            vertices.emplace_back(Vertex({-1.0f, -1.0f}, {0.0f, 0.0f}));

            auto& indices = VertexBuffer.GetIndices();
            indices.reserve(6);
            indices.insert(VertexBuffer.GetIndices().end(), {0, 1, 2, 2, 3, 0});

            VertexBuffer.UploadToGPU();
        }
    };

    Shader m_FrameShader;
    Frame m_FrameMesh;
};

class MSAAFramebuffer final
{
public:
    MSAAFramebuffer() = default;
    ~MSAAFramebuffer() = default;

    void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); }
    void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void Draw()
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_IFBO);
        glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // Draw 2D Frame Quad
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        glUseProgram(m_FrameShader.ID);
        glBindTexture(GL_TEXTURE_2D, m_TBO);
        m_FrameMesh.Draw();
    }

    void Create(int width, int height)
    {
        m_Width = width;
        m_Height = height;

        if (m_FrameShader.ID == 0)
            m_FrameShader = Shader("Shaders/PositionTexture.vert", "Shaders/PositionTexture.frag");

        // Delete previous buffers if they exist
        if (m_FBO != 0)
            glDeleteFramebuffers(1, &m_FBO);
        if (m_IFBO != 0)
            glDeleteFramebuffers(1, &m_IFBO);
        if (m_TBO != 0)
            glDeleteTextures(1, &m_TBO);
        if (m_MSTBO != 0)
            glDeleteTextures(1, &m_MSTBO);
        if (m_RBO != 0)
            glDeleteRenderbuffers(1, &m_RBO);

        // Frame buffer object
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // Mutli-sampled texture
        glGenTextures(1, &m_MSTBO);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_MSTBO);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_MSTBO, 0);

        // Render buffer object
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::println("Framebuffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Intermediate frame buffer object
        glGenFramebuffers(1, &m_IFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_IFBO);

        // Texture
        glGenTextures(1, &m_TBO);
        glBindTexture(GL_TEXTURE_2D, m_TBO);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TBO, 0);

        std::println("Created FBO: {}, IFBO: {}, TBO: {}, MSTBO: {}, RBO: {}", m_FBO, m_IFBO, m_TBO, m_MSTBO, m_RBO);
    }

    void Delete()
    {
        glDeleteFramebuffers(1, &m_FBO);
        glDeleteFramebuffers(1, &m_IFBO);
        glDeleteTextures(1, &m_TBO);
        glDeleteTextures(1, &m_MSTBO);
        glDeleteRenderbuffers(1, &m_RBO);
        std::println("Deleted FBO: {}, IFBO: {}, TBO: {}, MSTBO: {}, RBO: {}", m_FBO, m_IFBO, m_TBO, m_MSTBO, m_RBO);
    }

private:
    unsigned int m_FBO = 0;
    unsigned int m_TBO = 0;
    unsigned int m_RBO = 0;
    unsigned int m_IFBO = 0;
    unsigned int m_MSTBO = 0;

    int m_Width = 0;
    int m_Height = 0;

    class Frame : public MeshTemplate<Vertex2D<glm::vec2, glm::vec2>> // Position, Texture
    {
    public:
        Frame()
        {
            using Vertex = Vertex2D<glm::vec2, glm::vec2>;

            auto& vertices = VertexBuffer.GetVertices();
            vertices.reserve(4);
            vertices.emplace_back(Vertex({+1.0f, -1.0f}, {1.0f, 0.0f}));
            vertices.emplace_back(Vertex({+1.0f, +1.0f}, {1.0f, 1.0f}));
            vertices.emplace_back(Vertex({-1.0f, +1.0f}, {0.0f, 1.0f}));
            vertices.emplace_back(Vertex({-1.0f, -1.0f}, {0.0f, 0.0f}));

            auto& indices = VertexBuffer.GetIndices();
            indices.reserve(6);
            indices.insert(VertexBuffer.GetIndices().end(), {0, 1, 2, 2, 3, 0});

            VertexBuffer.UploadToGPU();
        }
    };

    Shader m_FrameShader;
    Frame m_FrameMesh;
};