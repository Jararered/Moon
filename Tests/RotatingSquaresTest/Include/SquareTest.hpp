#pragma once

#include <Moon.hpp>

#include <iostream>

class SquareMesh : public Mesh
{
public:
    SquareMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0, 1, 2, 2, 3, 0 });
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, 0.0f }, color, glm::vec3{0.0f, 0.0f, 1.0f});
        m_Geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, 0.0f }, color, glm::vec3{0.0f, 0.0f, 1.0f});
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, 0.0f }, color, glm::vec3{0.0f, 0.0f, 1.0f});
        m_Geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, 0.0f }, color, glm::vec3{0.0f, 0.0f, 1.0f});

        Generate();
    }
};

class SquareEntity : public Entity
{
public:
    SquareEntity(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f)
    {
        m_Position = position;

        glm::vec3 green = { 129.0f / 255.0f, 192.0f / 255.0f, 70.0f / 255.0f };
        glm::vec3 red = { 222.0f / 255.0f, 72.0f / 255.0f, 43.0f / 255.0f };
        glm::vec3 blue = { 59.0f / 255.0f, 119.0f / 255.0f, 188.0f / 255.0f };
        glm::vec3 yellow = { 252.0f / 255.0f, 207.0f / 255.0f, 3.0f / 255.0f };

        if (position.x >= 0.0f && position.y >= 0.0f)
            p_Mesh = new SquareMesh(green);
        else if (position.x < 0.0f && position.y >= 0.0f)
            p_Mesh = new SquareMesh(red);
        else if (position.x < 0.0f && position.y < 0.0f)
            p_Mesh = new SquareMesh(blue);
        else
            p_Mesh = new SquareMesh(yellow);

        glm::mat4 matrix = p_Mesh->GetTranslationMatrix();
        matrix = glm::translate(matrix, position);
        matrix = glm::scale(matrix, { scale, scale, scale });
        p_Mesh->SetTranslationMatrix(matrix);

        p_Collision = nullptr;
    }

    void Update(float dt) override
    {
        glm::mat4 rotation = p_Mesh->GetRotationMatrix();
        rotation = glm::rotate(rotation, glm::radians(dt * 1.0f * m_Position.x), glm::vec3(1.0f, 0.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(dt * 2.0f * m_Position.x), glm::vec3(0.0f, 1.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(dt * 3.0f * m_Position.x), glm::vec3(0.0f, 0.0f, 1.0f));
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

        auto window = Engine::GetWindow(spec);
        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto environment = new Environment;
        scenario->SetEnvironment(environment);

        auto camera = new Camera3D;
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int size = 40;
        int countx = 16;
        int county = 9;
        for (int i = -countx; i < countx + 1; i++)
        {
            for (int j = -county; j < county + 1; j++)
            {
                Entity* entity = new SquareEntity({ size * i, size * j, 0.0f }, size);
                entity->GetMesh()->SetShader(shader);
                scenario->AddEntity(entity);
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Update();
        }
    }
};