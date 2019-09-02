add_subdirectory (glfw-3.3)

add_subdirectory(glog)

add_subdirectory(gflags)

add_subdirectory(abseil-cpp)

include_directories(
    glfw-3.3/include/GLFW/
    glog/src/glog/
    gflags/include/
    stb_image/
)

