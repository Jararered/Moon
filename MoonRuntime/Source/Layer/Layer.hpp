#pragma once

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    void Initialize();
    virtual void Update();
    void Finalize();
};