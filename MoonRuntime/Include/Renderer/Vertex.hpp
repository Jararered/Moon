#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
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
        glEnableVertexAttribArray(2);
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
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, sizeof(T4) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex4D<T1, T2, T3, T4>), (void*)(sizeof(T1) + sizeof(T2) + sizeof(T3)));
        glEnableVertexAttribArray(3);
    }

private:
    T1 data1;
    T2 data2;
    T3 data3;
    T4 data4;
};

typedef Vertex1D<glm::vec2> Vertex1V2;
typedef Vertex1D<glm::vec3> Vertex1V3;
typedef Vertex1D<glm::vec4> Vertex1V4;
typedef Vertex2D<glm::vec2, glm::vec2> Vertex2V2;
typedef Vertex2D<glm::vec3, glm::vec3> Vertex2V3;
typedef Vertex2D<glm::vec4, glm::vec4> Vertex2V4;
typedef Vertex3D<glm::vec2, glm::vec2, glm::vec2> Vertex3V2;
typedef Vertex3D<glm::vec3, glm::vec3, glm::vec3> Vertex3V3;
typedef Vertex3D<glm::vec4, glm::vec4, glm::vec4> Vertex3V4;
typedef Vertex4D<glm::vec2, glm::vec2, glm::vec2, glm::vec2> Vertex4V2;
typedef Vertex4D<glm::vec3, glm::vec3, glm::vec3, glm::vec3> Vertex4V3;
typedef Vertex4D<glm::vec4, glm::vec4, glm::vec4, glm::vec4> Vertex4V4;