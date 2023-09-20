#pragma once

#include <glad/gl.h>
#include <print>
#include <stb_image.h>
#include <string>

struct Texture
{
    unsigned int ID = 0;
    int Width = 0;
    int Height = 0;
    int Channels = 0;

    Texture() = default;
    Texture(const std::string& textureFile)
    {
        // stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(textureFile.c_str(), &Width, &Height, &Channels, 0);
        if (!data)
        {
            std::println("Unable to load specified file: {}", textureFile);
        }

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        glGenerateMipmap(GL_TEXTURE_2D);

        // Repeat parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Disables upscaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
};