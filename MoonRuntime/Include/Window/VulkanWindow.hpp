#pragma once

class VulkanWindow : public Window
{
public:
    VulkanWindow() = default;
    virtual ~VulkanWindow() override = default;

    virtual void Update(float dt) override = 0;
    virtual bool IsRunning() override = 0;
    virtual Renderer& CreateRenderer() override = 0;
};