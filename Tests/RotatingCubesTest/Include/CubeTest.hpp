#pragma once

#include <Moon.hpp>

#include <iostream>

class CubeMesh : public Mesh
{
public:
    CubeMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_Geometry.Indices.insert(m_Geometry.Indices.end(), {
            0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20
            });

        // Front
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));

        // Back
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));

        // Right
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));

        // Left
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));

        // Top
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));

        // Bottom
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));

        Generate();
    }
};

class CubeEntity : public DynamicEntity
{
public:
    CubeEntity(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f)
    {
        m_Position = position;

        constexpr glm::vec3 red = { 222.0f / 255.0f, 72.0f / 255.0f, 43.0f / 255.0f };
        constexpr glm::vec3 green = { 129.0f / 255.0f, 192.0f / 255.0f, 70.0f / 255.0f };
        constexpr glm::vec3 blue = { 59.0f / 255.0f, 119.0f / 255.0f, 188.0f / 255.0f };
        constexpr glm::vec3 yellow = { 252.0f / 255.0f, 207.0f / 255.0f, 3.0f / 255.0f };
        constexpr glm::vec3 white = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };

        // if (position.x >= 0.0f && position.y >= 0.0f)
        //     p_Mesh = new CubeMesh(green);
        // else if (position.x < 0.0f && position.y >= 0.0f)
        //     p_Mesh = new CubeMesh(red);
        // else if (position.x < 0.0f && position.y < 0.0f)
        //     p_Mesh = new CubeMesh(blue);
        // else
        //     p_Mesh = new CubeMesh(yellow);

        p_Mesh = new CubeMesh(white);

        glm::mat4 matrix = p_Mesh->GetTranslationMatrix();
        matrix = glm::translate(matrix, position);
        matrix = glm::scale(matrix, { scale, scale, scale });
        p_Mesh->SetTranslationMatrix(matrix);

        p_Collision = nullptr;
    }

    void Update(float dt) override
    {
        glm::mat4 rotation = p_Mesh->GetRotationMatrix();
        rotation = glm::rotate(rotation, glm::radians(dt * m_Position.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(dt * m_Position.y), glm::vec3(0.0f, 1.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(dt * m_Position.z), glm::vec3(0.0f, 0.0f, 1.0f));
        p_Mesh->SetRotationMatrix(rotation);
    }
};

class Application : public Engine
{
public:
    void Start()
    {
        WindowSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;
        spec.VSync = true;
        spec.API = WindowSpecification::GraphicsAPI::OpenGL;

        auto window = GetWindow(spec);
        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto environment = new Environment;
        scenario->SetEnvironment(environment);

        auto camera = new Camera3D;
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int size = 25;
        int spacing = 50;
        int dimx = 5;
        int dimy = 5;
        int dimz = 5;
        for (int i = -dimx; i < dimx + 1; i++)
        {
            for (int j = -dimy; j < dimy + 1; j++)
            {
                for (int k = -dimz; k < dimz + 1; k++)
                {
                    Entity* entity = new CubeEntity({ spacing * i, spacing * j, spacing * k }, size);
                    entity->GetMesh()->SetShader(shader);
                    scenario->AddEntity(entity);
                }
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};