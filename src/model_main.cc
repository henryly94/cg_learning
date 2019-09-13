#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glog/logging.h>
#include <gflags/gflags.h>
#include <stb_image.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_split.h>
#include "shader.h"
#include "camera.h"
#include "model.h"

DEFINE_int32(window_height, 600, "Initial window height.");
DEFINE_int32(window_width, 600, "Initial window width");
DEFINE_int32(FPS, 60, "Refreshing rate every second.");
DEFINE_string(root_path, "../", "The path for project root.");
DEFINE_string(img_path, "resource/", "The path for img.");
DEFINE_string(shader_directory, "src/shaders/", "The path for shader files.");

using cg_learning::Camera;
using cg_learning::Model;
using cg_learning::Shader;

using absl::StrCat;
using absl::StrSplit;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f); 

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool firstMouse = true;

float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;

glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.updatePosition(Camera::FRONT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.updatePosition(Camera::BACK, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.updatePosition(Camera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.updatePosition(Camera::RIGHT, deltaTime);
}

void renderBackground() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Init(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;
    camera.updateFront(xoffset, yoffset);
}

int main(int argc, char** argv) {
    LOG(INFO) << "Initializing";
    Init(argc, argv);

    LOG(INFO) << "Creating GLFW window with height:" << FLAGS_window_height << " , width: " << FLAGS_window_width;
    GLFWwindow* window = glfwCreateWindow(FLAGS_window_width, FLAGS_window_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        LOG(FATAL) << "Failed to create GLFW window";
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG(FATAL) << "Failed to initialize GLAD";
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

    Shader shader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "light.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "multiple_light.fs"));
    Shader lampShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "light.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "lamp.fs"));
    glEnable(GL_DEPTH_TEST);

    Model nanosuit(StrCat(FLAGS_root_path, FLAGS_img_path, "models/nanosuit/nanosuit.obj").c_str());

    while(!glfwWindowShouldClose(window)) {

        processInput(window);
        
        renderBackground();

        shader.use();
        // directional light
        shader.setVec3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
        shader.setVec3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        shader.setVec3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        shader.setVec3f("pointLights[0].position", pointLightPositions[0]);
        shader.setVec3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09);
        shader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        shader.setVec3f("pointLights[1].position", pointLightPositions[1]);
        shader.setVec3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.09);
        shader.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        shader.setVec3f("pointLights[2].position", pointLightPositions[2]);
        shader.setVec3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3f("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3f("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.09);
        shader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        shader.setVec3f("pointLights[3].position", pointLightPositions[3]);
        shader.setVec3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3f("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3f("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.09);
        shader.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        shader.setVec3f("spotLight.position", camera.position);
        shader.setVec3f("spotLight.direction", camera.front);
        shader.setVec3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        shader.setVec3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        shader.setVec3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("spotLight.constant", 1.0f);
        shader.setFloat("spotLight.linear", 0.09);
        shader.setFloat("spotLight.quadratic", 0.032);
        shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)FLAGS_window_width / (float)FLAGS_window_height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // it's a bit too big for our scene, so scale it down
        glm::mat4 normal = model;
        normal = glm::inverse(normal);
        normal = glm::transpose(normal);
        shader.setMatrix4f("model", glm::value_ptr(model));
        shader.setMatrix4f("view", glm::value_ptr(view));
        shader.setMatrix4f("projection", glm::value_ptr(projection));
        shader.setMatrix4f("normalMat", glm::value_ptr(normal));
        shader.setVec3f("viewPos", {camera.position[0], camera.position[1], camera.position[2]});
    
        nanosuit.Draw(shader);
        lampShader.use();
        lampShader.setMatrix4f("view", glm::value_ptr(view));
        lampShader.setMatrix4f("projection", glm::value_ptr(projection));
        for (int i=0; i<4; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.setMatrix4f("model", glm::value_ptr(model));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();    

        // Update frame time.
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
    glfwTerminate();
    return 0;
}
