#pragma once

#include "Components/Mesh.hpp"
#include "Components/Shader.hpp"
#include "System.hpp"

class RenderSystem final : public System
{
public:
    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = default;
    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(const RenderSystem&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;
    ~RenderSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    void StartFramebuffer();
    void EndFramebuffer();
    void RenderFramebuffer();
    void ConfigureFramebuffer();

    unsigned int m_CurrentShader = 0;
    unsigned int m_CurrentTexture = 0;

    int m_Width = 0;
    int m_Height = 0;

    unsigned int m_FramebufferID;
    unsigned int m_ScreenTextureID;
    unsigned int m_RenderbufferID;

    void PollDebugControls();

    class ScreenMesh : public MeshTemplate<Vertex2D<glm::vec2, glm::vec2>> // Position, Texture
    {
    public:
        ScreenMesh()
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

    Entity m_Camera;
    Shader m_ScreenShader;
    ScreenMesh m_ScreenMesh;
};