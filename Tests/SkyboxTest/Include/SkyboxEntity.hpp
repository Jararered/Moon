#pragma once

#include <Entity.hpp>

#include "SkyboxMesh.hpp"

class SkyboxEntity : public Entity
{
public:
    SkyboxEntity() = default;
    virtual ~SkyboxEntity() = default;

    void Update(float dt) override
    {
        auto matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, *p_PositionReference);
        p_Mesh->SetTranslationMatrix(matrix);
    }

    void SetPositionReference(glm::vec3* position)
    {
        p_PositionReference = position;
    }

private:
    glm::vec3* p_PositionReference = nullptr;
};