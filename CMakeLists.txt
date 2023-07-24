cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

include_directories(
    MoonRuntime/Include/
    MoonRuntime/Include/Input/
    MoonRuntime/Include/Renderer/
    MoonRuntime/Include/Renderer/Camera
    MoonRuntime/Include/Shaders/

    Libraries/cereal/include/
    Libraries/FastNoiseLite/include/
    Libraries/glad/include/
    Libraries/glfw/include/
    Libraries/glm/include/
    Libraries/imgui/include/
    Libraries/stb_image/include/
)

link_directories(
    ../bin/
)

add_subdirectory(MoonRuntime)
add_subdirectory(MoonTestApp)


