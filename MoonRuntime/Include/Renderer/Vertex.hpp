#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glad/gl.h>

template <typename T1>
class Vertex1D
{
public:
    Vertex1D(T1 data1) : data1(data1) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex1D), (void*)(offsetof(Vertex1D, data1)));
        glEnableVertexAttribArray(0);
    }

private:
    T1 data1;
};

template <typename T1, typename T2>
class Vertex2D
{
public:
    Vertex2D(const T1& data1, const T2& data2) : data1(data1), data2(data2) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex2D<T1, T2>), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex2D<T1, T2>), (void*)(sizeof(T1)));
        glEnableVertexAttribArray(1);
    }

private:
    T1 data1;
    T2 data2;
};

template <typename T1, typename T2, typename T3>
class Vertex3D
{
public:
    Vertex3D(const T1& data1, const T2& data2, const T3& data3) : data1(data1), data2(data2), data3(data3) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex3D<T1, T2, T3>), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex3D<T1, T2, T3>), (void*)(sizeof(T1)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, sizeof(T3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex3D<T1, T2, T3>), (void*)(sizeof(T1) + sizeof(T2)));
        glEnableVertexAttribArray(1);
    }

private:
    T1 data1;
    T2 data2;
    T3 data3;
};

template <typename T1, typename T2, typename T3, typename T4>
class Vertex4D
{
public:
    Vertex4D(const T1& data1, const T2& data2, const T3& data3, const T4& data4) : data1(data1), data2(data2), data3(data3), data4(data4) {}

    static void EnableVertexAttributes()
    {
        glVertexAttribPointer(0, sizeof(T1) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, sizeof(T2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, sizeof(T3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, sizeof(T4) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2) + sizeof(T3)));
        glEnableVertexAttribArray(1);
    }

private:
    T1 data1;
    T2 data2;
    T3 data3;
    T4 data4;
};