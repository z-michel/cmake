# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_cmake)

set(PROJECT_NAME hello_cmake)

set(GN_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/gn)
set(GN_SAMPLE_APP_DIR ${GN_PREFIX}/examples/simple_build)

# Adding multiple different source files (hello_local.cpp) via the add_executable comman
add_executable(${PROJECT_NAME} main.cpp hello_local.cpp) # zach-dir/goodbye.cc)


######### Adding source from zach-dir ############

#This works for adding source from a different directory as a library
#add_library(zach-dir zach-dir/goodbye.cc)
#target_link_libraries(${PROJECT_NAME} PRIVATE zach-dir)

#Rely on the CMakeLists.txt in zach-dir
add_subdirectory(zach-dir)
target_link_libraries(${PROJECT_NAME} PRIVATE zach-dir)
target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/zach-dir
)


######### Adding GN as an external project ############


include(ExternalProject)

ExternalProject_Add(gn_externalProject
    SOURCE_DIR   ${GN_PREFIX}
    
  #  DOWNLOAD_DIR ${GN_PREFIX}
  # This doesn't work because it doesn't check if GN already exists before downloading
  #  DOWNLOAD_COMMAND git clone https://gn.googlesource.com/gn ${GN_PREFIX}

  # This doesn't work because it's not a git repository
  #DOWNLOAD_COMMAND URL https://gn.googlesource.com/gn/+archive/refs/heads/master.tar.gz

  # If moving forward with this, would create a ST GN Fork and download from there
  # DOWNLOAD_COMMAND URL [ST GN Git Repo]

    CONFIGURE_COMMAND python ${GN_PREFIX}/build/gen.py
      COMMAND ninja -C ${GN_PREFIX}/out
      COMMAND cd ${GN_SAMPLE_APP_DIR} && ../../out/gn gen -C out
    BUILD_COMMAND cd ${GN_SAMPLE_APP_DIR} && ninja -C out
    INSTALL_COMMAND ""

    BUILD_BYPRODUCTS
      {GN_SAMPLE_APP_DIR}/out/obj/libhello_static.a
)


add_library(gn STATIC IMPORTED)
add_dependencies(gn gn_externalProject)
set_target_properties(gn PROPERTIES IMPORTED_LOCATION ${GN_SAMPLE_APP_DIR}/out/obj/libhello_static.a) 
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${GN_SAMPLE_APP_DIR}
)
set(GN_LIBS
  gn
  CACHE INTERNAL "" FORCE
)
target_link_libraries(${PROJECT_NAME} PUBLIC gn)


#This works, but the CHIP repo will not have a CMakeLists.txt so can't do add_subdirectory
#Would we just do an add_library and add in all the source files we know from here?
#add_subdirectory(${GN_SAMPLE_APP_DIR})
#target_link_libraries(${PROJECT_NAME} PRIVATE gn_sample_app)
