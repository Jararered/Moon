#pragma once

#include <glad/gl.h>
#include <stb_image.h>
#include <string>

struct Texture
{
    unsigned int ID = 0;

    Texture() = default;
    Texture(std::string_view textureFile)
    {
        int width = 0;
        int height = 0;
        int channels = 0;

        stbi_set_flip_vertically_on_load(true);

        auto data = stbi_load(textureFile.data(), &width, &height, &channels, 0);
        if (not data)
        {
            return;
        }

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};