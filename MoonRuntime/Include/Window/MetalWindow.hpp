#pragma once

class MetalWindow : public Window
{
public:
    MetalWindow() = default;
    virtual ~MetalWindow() override = default;

    virtual void Update(float dt) override = 0;
    virtual bool IsRunning() override = 0;
    virtual Renderer& CreateRenderer() override = 0;
};