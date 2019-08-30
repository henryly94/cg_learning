#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

int main() {
        if (!glfwInit()) {
                fprintf(stderr, "Failed to initialize GLFW\n");
                getchar();
                return -1;
        }

        auto window = glfwCreateWindow(1024, 768, "My Window", NULL, NULL);
        if (window == NULL) {
            fprintf(stderr, "Failed to open GLFW window.\n");
            getchar();
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        
        if (glewInit() != GLEW_OK) {
                fprintf(stderr, "Failed to initialize GLEW\n");
                getchar();
                glfwTerminate();
                return -1;
        }

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

        do {
                glClear(GL_COLOR_BUFFER_BIT);

                glfwSwapBuffers(window);
                glfwPollEvents();
        }while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
                        glfwWindowShouldClose(window) == 0);

        glfwTerminate();
        return 0;
}
