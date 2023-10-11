#pragma once

#include <glad/gl.h>
#include <stb_image.h>
#include <string>

struct Texture
{
    unsigned int ID = 0;
    int Width = 0;
    int Height = 0;
    int Channels = 0;

    Texture() = default;
    Texture(std::string_view textureFile)
    {
        stbi_set_flip_vertically_on_load(true);

        unsigned char* data = stbi_load(textureFile.data(), &Width, &Height, &Channels, 0);
        if (not data)
        {
            return;
        }

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        glGenerateMipmap(GL_TEXTURE_2D);

        // Repeat parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Disables upscaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
};