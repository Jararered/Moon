cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_DEBUG_POSTFIX -debug)

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)
file(GLOB_RECURSE ProjectHeaderFiles Include/*.hpp)

set(LibrarySourceFiles
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/source/imgui.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/glad/source/gl.c
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/source/stb_image.cpp
)

add_library(${Project}
    ${ProjectSourceFiles}
    ${ProjectHeaderFiles}
    ${LibrarySourceFiles}
)

if(UNIX)
    add_definitions(-DUNIX)
    find_package(glfw3 3.3.8 REQUIRED)
endif(UNIX)

if(WIN32)
    target_link_libraries(${Project} ${CMAKE_SOURCE_DIR}/Libraries/glfw/lib/glfw3.lib)
endif(WIN32)

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

target_include_directories(
    ${Project}
    PUBLIC
    ${MoonIncludeDirs}
    ${LibraryIncludeDirs}
)