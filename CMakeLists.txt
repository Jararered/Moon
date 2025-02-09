cmake_minimum_required(VERSION 3.26)

project(Moon)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Linux)
elseif(WIN32)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Windows)
elseif(APPLE)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/MacOS)
endif()

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
add_subdirectory(MoonSandbox)
