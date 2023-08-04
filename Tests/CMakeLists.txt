cmake_minimum_required(VERSION 3.26)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

add_subdirectory(LayerTest)
add_subdirectory(PlanetTest)
add_subdirectory(SkyboxTest)
add_subdirectory(CirclePhysicsTest)