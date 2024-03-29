# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (CGLearning)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_TESTING OFF)

find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
    external/glfw-3.3/include/
    external/glad/include/
    external/glog/src/glog/
    external/gflags/include/
    external/stb_image/
    external/glm/
    external/assimp-4.1.0/include/
    build/external/assimp-4.1.0/include/
)

set(INTERNAL_SOURCE
    src/shader.cc
    src/camera.cc
    src/model.cc
    src/mesh.cc
    src/util.cc
)

set(EXTERNAL_SOURCE
    external/glad/src/glad.c
    external/stb_image/stb_image.cc
)

set(EXTERNAL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    glog::glog
    gflags::gflags
    absl::strings
    assimp
)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
)

add_executable(
    render
    src/render.cc
    src/shader.cc
    src/camera.cc
    ${EXTERNAL_SOURCE}
)

target_link_libraries(
    render
    ${EXTERNAL_LIBS}
)

add_executable(
    light
    src/light.cc
    ${INTERNAL_SOURCE}
    ${EXTERNAL_SOURCE}
)

target_link_libraries(
    light
    ${EXTERNAL_LIBS}
)

add_executable(
    model
    src/model_main.cc
    ${INTERNAL_SOURCE}
    ${EXTERNAL_SOURCE}
)

target_link_libraries(
    model
    ${EXTERNAL_LIBS}
)

add_executable(
    depth
    src/depth.cc
    ${INTERNAL_SOURCE}
    ${EXTERNAL_SOURCE}
)

target_link_libraries(
    depth
    ${EXTERNAL_LIBS}
)
