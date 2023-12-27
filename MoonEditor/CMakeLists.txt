cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

set(ImguiSourceFiles
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(${Project} ${ProjectSourceFiles} ${ImguiSourceFiles})

target_include_directories(${Project} PUBLIC Source ${MoonIncludeDirs})
target_link_libraries(${Project} MoonRuntime)

install(DIRECTORY Resources DESTINATION ${InstallDir})
install(TARGETS ${Project} RUNTIME DESTINATION ${InstallDir})