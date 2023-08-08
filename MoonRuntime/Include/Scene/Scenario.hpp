#pragma once

#include <vector>

#include "Camera.hpp"
#include "Entity.hpp"
#include "Skybox.hpp"

class Scenario
{
public:
    Scenario() = default;
    virtual ~Scenario() = default;

    void Update(float dt)
    {
        for (auto entity : m_Entities)
            entity->Update(dt);

        // UpdateCollisions(dt);
        // UpdateBoundaries(dt);

        if (p_Camera)
            p_Camera->Update(dt);
    }

    void SetSkybox(const std::string& file)
    {
        if (!p_Camera)
            return;

        if (!p_Skybox)
            p_Skybox = new SkyboxEntity;

        auto skyboxMesh = new SkyboxMesh;
        p_Skybox->SetMesh(skyboxMesh);

        auto skyboxTexture = Texture(file);
        p_Skybox->GetMesh()->SetTexture(skyboxTexture);

        auto skyboxShader = Shader();
        skyboxShader.Compile("Shaders/Skybox.vert", "Shaders/Skybox.frag");
        p_Skybox->GetMesh()->SetShader(skyboxShader);

        p_Skybox->SetPositionReference(&p_Camera->GetPosition());
    }

private:
    Camera* p_Camera = nullptr;
    SkyboxEntity* p_Skybox = nullptr;

    std::vector<Entity*> m_Entities;

public:
    Camera* GetCamera() const { return p_Camera; }
    void SetCamera(Camera* camera) { p_Camera = camera; }

    SkyboxEntity* GetSkybox() const { return p_Skybox; }
    void SetSkybox(SkyboxEntity* skybox) { p_Skybox = skybox; }

    void AddEntity(Entity* entity) { m_Entities.push_back(entity); }
    std::vector<Entity*> GetEntities() const { return m_Entities; }
};