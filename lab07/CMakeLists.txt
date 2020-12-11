cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

project(lab07)

find_package(GLUT REQUIRED)

add_executable(lab07 main.cpp)

target_link_libraries(lab07 PRIVATE GLUT::GLUT)
