#pragma once

#include "System.hpp"

class IndexSystem final : public System
{
public:
    IndexSystem() = default;
    IndexSystem(const IndexSystem&) = delete;
    IndexSystem(IndexSystem&&) = delete;
    IndexSystem& operator=(const IndexSystem&) = delete;
    IndexSystem& operator=(IndexSystem&&) = delete;
    ~IndexSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;

private:
    float m_Scale;
};