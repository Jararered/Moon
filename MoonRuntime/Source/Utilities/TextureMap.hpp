#pragma once

#include <glm/vec2.hpp>
#include <vector>

class TextureMap
{
public:
    TextureMap(int width, int height, int resolution) : m_Width(width), m_Height(height), m_Resolution(resolution)
    {
        if (not(width > 0) or not(width < 10000) or not(height > 0) or not(height < 10000))
        {
            return;
        }

        float x, y, left, bottom, right, top;

        for (int j = 0; j < m_Height; j += resolution)
        {
            for (int i = 0; i < m_Width; i += resolution)
            {
                x = static_cast<float>(i);
                y = static_cast<float>(j);

                left = x / static_cast<float>(m_Width);
                bottom = y / static_cast<float>(m_Height);

                right = (x + static_cast<float>(resolution)) / static_cast<float>(m_Width);
                top = (y + static_cast<float>(resolution)) / static_cast<float>(m_Height);

                m_Coordinates.push_back({left, right, bottom, top});
            }
        }
    }

    glm::vec2 TopLeft(int index) const { return {m_Coordinates[index][0], m_Coordinates[index][2]}; }
    glm::vec2 TopRight(int index) const { return {m_Coordinates[index][1], m_Coordinates[index][2]}; }
    glm::vec2 BottomLeft(int index) const { return {m_Coordinates[index][0], m_Coordinates[index][3]}; }
    glm::vec2 BottomRight(int index) const { return {m_Coordinates[index][1], m_Coordinates[index][3]}; }

private:
    int m_Width = 0;
    int m_Height = 0;
    int m_Resolution = 0;
    std::vector<std::vector<float>> m_Coordinates;
};