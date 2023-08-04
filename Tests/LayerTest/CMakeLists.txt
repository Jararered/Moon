cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

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
    ${LibraryIncludeDirs}
)

if(UNIX)
    add_definitions(-DUNIX)
    find_package(glfw3 3.3.8 REQUIRED)
    target_link_libraries(${Project} glfw)
endif(UNIX)

if(WIN32)
    target_link_directories(${Project} PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/glfw/lib)
endif(WIN32)

target_link_libraries(
    ${Project}
    MoonRuntime
)

install(TARGETS ${Project} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/Build/Tests/${Project})
install(DIRECTORY Shaders DESTINATION ${CMAKE_SOURCE_DIR}/Build/Tests/${Project})