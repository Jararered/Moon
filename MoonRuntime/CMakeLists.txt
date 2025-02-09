cmake_minimum_required(VERSION 3.26)

add_library(MoonRuntime)

file(GLOB_RECURSE ProjectSourceFiles
    Source/*.cpp
)

set(LibrarySourceFiles
    ${CMAKE_SOURCE_DIR}/Libraries/glad/source/gl.c
    ${CMAKE_SOURCE_DIR}/Libraries/stb_image/source/stb_image.cpp
)

target_sources(MoonRuntime
PRIVATE
    ${ProjectSourceFiles}
    ${LibrarySourceFiles}
)

if(WIN32)
    target_link_libraries(MoonRuntime
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Libraries/glfw/lib/glfw3.lib
    )
endif()

if(UNIX)
    target_compile_definitions(MoonRuntime
    PRIVATE
        UNIX
    )

    find_package(glfw3)
    target_link_libraries(MoonRuntime
    PRIVATE
        glfw
    )
endif()

target_compile_definitions(MoonRuntime
PRIVATE
    GLFW_INCLUDE_NONE
    GLM_ENABLE_EXPERIMENTAL
)

target_include_directories(MoonRuntime
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Moon
    ${LibraryIncludeDirs}
)

install(DIRECTORY Resources DESTINATION ./)