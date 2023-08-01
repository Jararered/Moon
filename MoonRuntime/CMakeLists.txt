cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_DEBUG_POSTFIX -debug)

if(UNIX)
    add_definitions(-DUNIX)
endif(UNIX)

find_package(glfw3 3.3.8 REQUIRED)
add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)
file(GLOB_RECURSE ProjectHeaderFiles Include/*.hpp)

set(LibrarySourceFiles
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/glad/source/gl.c
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/source/stb_image.cpp
)

add_library(${Project}
    ${ProjectSourceFiles}
    ${ProjectHeaderFiles}
    ${LibrarySourceFiles}
)

target_include_directories(
    ${Project}
    PUBLIC
    ${MoonIncludeDirs}
    ${LibraryIncludeDirs}
)