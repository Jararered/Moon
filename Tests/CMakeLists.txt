cmake_minimum_required(VERSION 3.27)

get_filename_component(Project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${Project})

# add_subdirectory(RotatingSquaresTest2D)
# add_subdirectory(RotatingSquaresTest3D)
# add_subdirectory(RotatingCubesTest)
# add_subdirectory(DirectionLightTest)
# add_subdirectory(PositionLightTest)
# add_subdirectory(SquaresPhysicsTest)
# add_subdirectory(PlanetTest)
# add_subdirectory(WorldTest)
add_subdirectory(SkyboxTest)