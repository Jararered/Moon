cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_CXX_STANDARD 23)

set(InstallDir ${CMAKE_SOURCE_DIR})

set(MoonIncludeDirs
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/Components
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/ECS
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/Layer
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/Systems
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/Utilities
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/Window)

set(LibraryIncludeDirs
    ${CMAKE_SOURCE_DIR}/Libraries/FastNoiseLite/include
    ${CMAKE_SOURCE_DIR}/Libraries/glad/include
    ${CMAKE_SOURCE_DIR}/Libraries/glfw/include
    ${CMAKE_SOURCE_DIR}/Libraries/glm/include
    ${CMAKE_SOURCE_DIR}/Libraries/octree/include
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/include
    ${CMAKE_SOURCE_DIR}/Libraries/imgui
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/backends
)

add_subdirectory(MoonRuntime)
add_subdirectory(Sandbox)
