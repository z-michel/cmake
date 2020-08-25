# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_cmake)

# Add an executable
add_executable(hello_cmake main.cpp)

include(ExternalProject)

ExternalProject_Add(gn_externalProject
    SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/lib/gn/examples/simple_build/"
    CONFIGURE_COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/lib/gn/build/gen.py
      COMMAND $ENV{VAR} ninja -C ${CMAKE_CURRENT_SOURCE_DIR}/lib/gn/out
      COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/gn/examples/simple_build && ../../out/gn gen -C out
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/gn/examples/simple_build && ninja -C out
    INSTALL_COMMAND :
)
