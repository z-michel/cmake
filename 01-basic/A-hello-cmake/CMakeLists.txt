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
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND scp ${CMAKE_CURRENT_SOURCE_DIR}/lib/gn/examples/simple_build/out/hello ${CMAKE_CURRENT_SOURCE_DIR}
)

ExternalProject_Add(chip_externalProject
    SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/lib/chip"
    CONFIGURE_COMMAND source ${CMAKE_CURRENT_SOURCE_DIR}/lib/chip/scripts/activate.sh
      COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/chip && gn gen out/host
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/chip && ninja -C out/host
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)

#add_library(gn STATIC IMPORTED)
#add_dependencies(gn gn_externalProject)

#add_executable(hello)