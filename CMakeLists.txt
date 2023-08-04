cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set (CMAKE_CXX_STANDARD 23)

set(InstallDir ${CMAKE_SOURCE_DIR})

set(MoonIncludeDirs
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Collider
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Renderer
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Scene
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Window
)

set(LibraryIncludeDirs
    ${CMAKE_SOURCE_DIR}/Libraries/cereal/include
    ${CMAKE_SOURCE_DIR}/Libraries/octree/include
    ${CMAKE_SOURCE_DIR}/Libraries/FastNoiseLite/include
    ${CMAKE_SOURCE_DIR}/Libraries/glad/include
    ${CMAKE_SOURCE_DIR}/Libraries/glfw/include
    ${CMAKE_SOURCE_DIR}/Libraries/glm/include
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/include
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/include
)
 
add_subdirectory(MoonRuntime)
add_subdirectory(Tests)