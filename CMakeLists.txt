# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (CGLearning)

add_subdirectory (external)


include_directories(
    external/glfw-3.1.2/include/
    external/glm-0.9.7.1/
    external/glew-1.13.0/include/
    .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130
)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

add_executable(
    render
    src/render.cpp
)

target_link_libraries(
    render
    ${ALL_LIBS}
)

add_custom_command(
        TARGET render POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/render${CMAKE_EXECUTABLE_SUFFIX}"
        "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
)



