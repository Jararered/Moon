#pragma once

#include <string>

class Texture
{
public:
    Texture() = default;
    ~Texture() = default;

    void Create(const std::string& file);
    void Delete();
    void Bind();
    void Unbind();

private:
    int m_Width;
    int m_Height;
    int m_ChannelCount;
    unsigned int m_ID;

public:
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    int GetChannelCount() const { return m_ChannelCount; }
    unsigned int GetID() const { return m_ID; }
};
