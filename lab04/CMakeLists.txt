cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

project(lab04)

#find_package(OpenGL REQUIRED)

find_package(GLUT REQUIRED)

add_executable(lab04 main.cpp)

## Additional Include Directories
#include_directories(${OpenGL_INCLUDE_DIRS})
#
#message("${OpenGL_INCLUDE_DIRS}")
#
## Additional Library Directories
#link_directories(${OpenGL_LIB_DIR})
#
## Additional Dependencies
#target_link_libraries(lab04 ${OpenGL_LIBS})

target_link_libraries(lab04 PRIVATE GLUT::GLUT)
