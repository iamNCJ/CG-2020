cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

project(lab09)

add_executable(lab09 main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
if(WIN32)
find_package(GLEW REQUIRED)
endif()

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    target_link_libraries(lab09 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
elseif(WIN32)
    # for Windows operating system in general
    target_link_libraries(lab09 PRIVATE GLUT::GLUT GLEW::GLEW)
endif()
