#pragma once

#include <glad/gl.h>
#include <stb_image.h>

#include <iostream>
#include <string>

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& file) { Create(file); }
    virtual ~Texture() = default;

    void Create(const std::string& file)
    {
        unsigned char* data = stbi_load(file.c_str(), &m_Width, &m_Height, &m_Channels, 0);
        if (!data)
        {
            std::cout << "Texture::Create(): Unable to load specified file. (" << file << ")\n";
            return;
        }

        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        // Repeat parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Disables upscaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void Delete() { glDeleteTextures(1, &m_ID); }

    void Bind() { glBindTexture(GL_TEXTURE_2D, m_ID); }

    void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

private:
    int m_Width;
    int m_Height;
    int m_Channels;
    unsigned int m_ID;

public:
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    int GetChannelCount() const { return m_Channels; }
    unsigned int GetID() const { return m_ID; }
};
