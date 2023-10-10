cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)
file(GLOB_RECURSE ProjectHeaderFiles Source/*.hpp)

file(GLOB_RECURSE ProjectScriptFiles Scripts/*.hpp)

add_executable(${Project} ${ProjectSourceFiles} ${ProjectHeaderFiles} ${ProjectScriptFiles})

target_include_directories(${Project} PUBLIC Source)
target_link_libraries(${Project} MoonRuntime)

install(DIRECTORY Shaders DESTINATION ${CMAKE_SOURCE_DIR}/Build/Sandbox)
install(DIRECTORY Textures DESTINATION ${CMAKE_SOURCE_DIR}/Build/Sandbox)