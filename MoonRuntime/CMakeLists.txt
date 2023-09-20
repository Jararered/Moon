cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

set(CMAKE_DEBUG_POSTFIX -debug)

file(GLOB_RECURSE ProjectSourceFiles Source/*.cpp)
file(GLOB_RECURSE ProjectHeaderFiles Source/*.hpp)

set(LibrarySourceFiles
    ${CMAKE_SOURCE_DIR}/Libraries/glad/source/gl.c
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/source/stb_image.cpp)

add_library(${Project} ${ProjectSourceFiles} ${ProjectHeaderFiles}
                       ${LibrarySourceFiles})

if(UNIX)
  add_definitions(-DUNIX)
  find_package(glfw3 3.3.8 REQUIRED)
endif(UNIX)

if(WIN32)
  target_link_libraries(${Project}
                        ${CMAKE_SOURCE_DIR}/Libraries/glfw/lib/glfw3.lib)
endif(WIN32)

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

target_include_directories(${Project} PUBLIC ${MoonIncludeDirs}
                                             ${LibraryIncludeDirs})

# if(MSVC) target_compile_options(${Project} PRIVATE /W4 /WX) else()
# target_compile_options(${Project} PRIVATE -Wall -Wextra -Wpedantic -Werror)
# endif()
