cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_CXX_STANDARD 23)

if(UNIX)
    set(InstallDir ${CMAKE_SOURCE_DIR}/Linux)\
endif()

if(WIN32)
    set(InstallDir ${CMAKE_SOURCE_DIR}/Windows)
endif()

if(APPLE)
    set(InstallDir ${CMAKE_SOURCE_DIR}/MacOS)
endif()

set(MoonIncludeDirs
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Source/Moon
)

set(LibraryIncludeDirs
    ${CMAKE_SOURCE_DIR}/Libraries/FastNoiseLite/include
    ${CMAKE_SOURCE_DIR}/Libraries/glad/include
    ${CMAKE_SOURCE_DIR}/Libraries/glfw/include
    ${CMAKE_SOURCE_DIR}/Libraries/glm/include
    ${CMAKE_SOURCE_DIR}/Libraries/imgui
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/backends
    ${CMAKE_SOURCE_DIR}/Libraries/octree/include
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/include
)

add_subdirectory(MoonRuntime)
add_subdirectory(MoonEditor)
