# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (CGLearning)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
    external/glfw-3.3/include/
    external/glad/include/
    external/glog/src/glog/
)

set(GLAD_SOURCE
    external/glad/src/glad.c
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    glog::glog
)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
)


add_executable(
    render
    src/render.cc
    ${GLAD_SOURCE}
)

target_link_libraries(
    render
    ${ALL_LIBS}
)



