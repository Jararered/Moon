#pragma once

#include "System.hpp"

class IndexSystem final : public System
{
public:
    IndexSystem() = default;
    IndexSystem(const IndexSystem&) = default;
    IndexSystem(IndexSystem&&) = default;
    IndexSystem& operator=(const IndexSystem&) = default;
    IndexSystem& operator=(IndexSystem&&) = default;
    ~IndexSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    float m_Scale;
};