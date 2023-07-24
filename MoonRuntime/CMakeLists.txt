cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_DEBUG_POSTFIX -debug)

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

find_package(glfw3 3.3.8 REQUIRED)

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

add_library(
    ${Project}
    ${ProjectSourceFiles}
    ${LibrarySourceFiles}
)

install(TARGETS ${Project} ARCHIVE DESTINATION ${InstallDir}/lib)