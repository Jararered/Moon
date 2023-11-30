#pragma once

#include <glad/gl.h>

// Types intended to be used with these templates
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Moon
{

    template <typename T1> class Vertex1D final
    {
    public:
        Vertex1D(const T1& data1) : m_Data1(data1) {}

        static void EnableVertexAttributes()
        {
            glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex1D<T1>), (void*)(0));
            glEnableVertexAttribArray(0);
        }

    private:
        T1 m_Data1;
    };

    template <typename T1, typename T2> class Vertex2D final
    {
    public:
        Vertex2D(const T1& data1, const T2& data2) : m_Data1(data1), m_Data2(data2) {}

        static void EnableVertexAttributes()
        {
            glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex2D<T1, T2>), (void*)(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex2D<T1, T2>), (void*)(sizeof(T1)));
            glEnableVertexAttribArray(1);
        }

    private:
        T1 m_Data1;
        T2 m_Data2;
    };

    template <typename T1, typename T2, typename T3> class Vertex3D final
    {
    public:
        Vertex3D(const T1& data1, const T2& data2, const T3& data3) : m_Data1(data1), m_Data2(data2), m_Data3(data3) {}

        static void EnableVertexAttributes()
        {
            glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex3D<T1, T2, T3>), (void*)(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex3D<T1, T2, T3>), (void*)(sizeof(T1)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, sizeof(T3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex3D<T1, T2, T3>), (void*)(sizeof(T1) + sizeof(T2)));
            glEnableVertexAttribArray(2);
        }

    private:
        T1 m_Data1;
        T2 m_Data2;
        T3 m_Data3;
    };

    template <typename T1, typename T2, typename T3, typename T4> class Vertex4D final
    {
    public:
        Vertex4D(const T1& data1, const T2& data2, const T3& data3, const T4& data4) : m_Data1(data1), m_Data2(data2), m_Data3(data3), m_Data4(data4) {}

        static void EnableVertexAttributes()
        {
            glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, sizeof(T3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(3, sizeof(T4) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2) + sizeof(T3)));
            glEnableVertexAttribArray(3);
        }

    private:
        T1 m_Data1;
        T2 m_Data2;
        T3 m_Data3;
        T4 m_Data4;
    };
}