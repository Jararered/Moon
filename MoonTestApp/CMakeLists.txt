cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_DEBUG_POSTFIX -debug)

# Added so that glad would shut the fuck up
add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

find_package(glfw3 3.3.8 REQUIRED)

# Moon Test App files
file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)

add_executable(
    ${Project}
    ${ProjectSourceFiles}
    ${LibrarySourceFiles}
)

target_link_libraries(
    ${Project}
    glfw
    MoonRuntime
)

install(TARGETS ${Project} ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/bin)