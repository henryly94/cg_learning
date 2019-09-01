add_subdirectory (glfw-3.3)

add_subdirectory(glog)

include_directories(
    glfw-3.3/include/GLFW/
    glog/src/glog/
)

