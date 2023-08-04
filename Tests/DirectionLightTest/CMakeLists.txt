cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

find_package(glfw3 3.3.8 REQUIRED)

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

add_executable(
    ${Project}
    ${ProjectSourceFiles}
    ${LibrarySourceFiles}
)

target_include_directories(
    ${Project}
    PUBLIC
    Include
    ${MoonIncludeDirs}
)

target_link_libraries(
    ${Project}
    glfw
    MoonRuntime
)

install(DIRECTORY Shaders DESTINATION ${InstallDir}/build/Tests/${Project})