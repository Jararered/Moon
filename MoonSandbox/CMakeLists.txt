cmake_minimum_required(VERSION 3.26)

add_executable(MoonSandbox)

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

set(ImguiSourceFiles
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Libraries/imgui/backends/imgui_impl_opengl3.cpp
)

target_sources(MoonSandbox 
PRIVATE 
    ${ProjectSourceFiles} 
    ${ImguiSourceFiles}
)

target_include_directories(MoonSandbox 
PRIVATE 
    Source 
)

target_link_libraries(MoonSandbox PRIVATE MoonRuntime)

install(TARGETS MoonSandbox RUNTIME DESTINATION ./)
install(DIRECTORY Resources DESTINATION ./)