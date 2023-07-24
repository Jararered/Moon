cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_DEBUG_POSTFIX -debug)

# Added so that glad would shut the fuck up
add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

find_package(glfw3 3.3 REQUIRED)

# Moon Test App files
file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

add_executable(
    ${Project}

    ${ProjectSourceFiles}
    ../Libraries/imgui/source/imgui_draw.cpp
    ../Libraries/imgui/source/imgui_impl_glfw.cpp
    ../Libraries/imgui/source/imgui_impl_opengl3.cpp
    ../Libraries/imgui/source/imgui_tables.cpp
    ../Libraries/imgui/source/imgui_widgets.cpp
    ../Libraries/imgui/source/imgui.cpp
    ../Libraries/glad/source/gl.c
    ../Libraries/stb_image/source/stb_image.cpp
)

target_link_libraries(
    ${Project}
    
    MoonRuntime
)

install(TARGETS ${Project} ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/bin)