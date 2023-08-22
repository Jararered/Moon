#pragma once

#include "Debug.hpp"

#include <stb_image.h>
#include <string>

struct Texture
{
    unsigned int ID = 0;

    static unsigned int CreateTexture(const std::string& textureFile)
    {
        int width, height, channels;
        unsigned char* data = stbi_load(textureFile.c_str(), &width, &height, &channels, 0);
        if (!data)
        {
            DebugOutput("Unable to load specified file. (" << textureFile << ")");
            return 0;
        }

        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        // Repeat parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Disables upscaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        return id;
    }
};