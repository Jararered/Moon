#pragma once

class BufferInterface
{
public:
    virtual ~BufferInterface() = default;

    virtual void BufferData() = 0;
    virtual void Delete() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void Draw() = 0;
    virtual void Update() = 0;
};