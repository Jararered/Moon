#pragma once

#include <glad/gl.h>

template <typename T1> struct Vertex1D
{
    Vertex1D(const T1& data1) : m_Data1(data1) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex1D<T1>), (void*)(0));
        glEnableVertexAttribArray(0);
    }

    T1 m_Data1;
};

template <typename T1, typename T2> struct Vertex2D
{
    Vertex2D(const T1& data1, const T2& data2) : m_Data1(data1), m_Data2(data2) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex2D<T1, T2>), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex2D<T1, T2>), (void*)(sizeof(T1)));
        glEnableVertexAttribArray(1);
    }

    T1 m_Data1;
    T2 m_Data2;
};

template <typename T1, typename T2, typename T3> struct Vertex3D
{
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

    T1 m_Data1;
    T2 m_Data2;
    T3 m_Data3;
};

template <typename T1, typename T2, typename T3, typename T4> struct Vertex4D
{
    Vertex4D(const T1& data1, const T2& data2, const T3& data3, const T4& data4) : m_Data1(data1), m_Data2(data2), m_Data3(data3), m_Data4(data4) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, sizeof(T3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, sizeof(T4) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2) + sizeof(T3)));
        glEnableVertexAttribArray(3);
    }

    T1 m_Data1;
    T2 m_Data2;
    T3 m_Data3;
    T4 m_Data4;
};