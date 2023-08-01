cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(InstallDir ${CMAKE_SOURCE_DIR})

include_directories(
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Collider/
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Renderer/
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Scene/
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Window/
    ${CMAKE_SOURCE_DIR}/MoonRuntime/Include/Window/Input/

    ${CMAKE_SOURCE_DIR}/Libraries/cereal/include/
    ${CMAKE_SOURCE_DIR}/Libraries/FastNoiseLite/include/
    ${CMAKE_SOURCE_DIR}/Libraries/glad/include/
    ${CMAKE_SOURCE_DIR}/Libraries/glfw/include/
    ${CMAKE_SOURCE_DIR}/Libraries/glm/include/
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/include/
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/include/
)

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

if(UNIX)
    add_definitions(-DUNIX)
endif(UNIX)
 
add_subdirectory(MoonRuntime)

# add_subdirectory(Tests/RotatingSquaresTest2D)
# add_subdirectory(Tests/RotatingSquaresTest3D)
# add_subdirectory(Tests/RotatingCubesTest)
# add_subdirectory(Tests/DirectionLightTest)
add_subdirectory(Tests/PositionLightTest)
# add_subdirectory(Tests/SquaresPhysicsTest)
# add_subdirectory(Tests/PlanetTest)
# add_subdirectory(Tests/WorldTest)
