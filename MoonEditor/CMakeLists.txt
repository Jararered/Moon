cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

add_executable(${Project} ${ProjectSourceFiles})

target_include_directories(${Project} PUBLIC Source)
target_link_libraries(${Project} MoonRuntime)

install(DIRECTORY Shader DESTINATION ${CMAKE_SOURCE_DIR}/Build/${Project})
install(DIRECTORY Texture DESTINATION ${CMAKE_SOURCE_DIR}/Build/${Project})
install(DIRECTORY Font DESTINATION ${CMAKE_SOURCE_DIR}/Build/${Project})