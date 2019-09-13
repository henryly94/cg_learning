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

DEFINE_int32(window_height, 600, "Initial window height.");
DEFINE_int32(window_width, 600, "Initial window width");
DEFINE_int32(FPS, 60, "Refreshing rate every second.");
DEFINE_string(root_path, "../", "The path for project root.");
DEFINE_string(img_path, "resource/", "The path for img.");
DEFINE_string(shader_directory, "src/shaders/", "The path for shader files.");

using cg_learning::Camera;
using cg_learning::Shader;
using absl::StrCat;
using absl::StrSplit;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f); 

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool firstMouse = true;

float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

unsigned int GetTextureFromFile(const std::string& file_name){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
    int width, height, nrChannels;
    std::string img_file_path = StrCat(FLAGS_root_path, FLAGS_img_path, file_name);
    stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(img_file_path.c_str(), &width, &height, &nrChannels, 0);
		if (!data) {
			LOG(FATAL) << "Failed when loading image from " << FLAGS_img_path; 
		}
    std::vector<std::string> tmp = StrSplit(file_name, '.'); 
    std::string& suffix = tmp.back();
    if (suffix == "jpg") {
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (suffix == "png") {
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
      LOG(FATAL) << "Image file with suffix: ." << suffix << " is not supported yet.";
    }
    glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
    return texture;
}

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

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
     
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    unsigned int wood = GetTextureFromFile(StrCat(FLAGS_root_path, FLAGS_img_path, "wood2.png"));
    unsigned int wood_spec = GetTextureFromFile(StrCat(FLAGS_root_path, FLAGS_img_path, "wood2_specular.png"));

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
        shader.setInt("material.diffuse", 0);
        shader.setInt("material.specular", 0);
        shader.setFloat("material.shininess", 64.0f);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)FLAGS_window_width / (float)FLAGS_window_height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);
        glm::mat4 normal = model;
        normal = glm::inverse(normal);
        normal = glm::transpose(normal);
        shader.setMatrix4f("model", glm::value_ptr(model));
        shader.setMatrix4f("view", glm::value_ptr(view));
        shader.setMatrix4f("projection", glm::value_ptr(projection));
        shader.setMatrix4f("normalMat", glm::value_ptr(normal));
        shader.setVec3f("viewPos", {camera.position[0], camera.position[1], camera.position[2]});
    
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wood);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, wood_spec);
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glm::mat4 normal = model;
            normal = glm::inverse(normal);
            normal = glm::transpose(normal);
            shader.setMatrix4f("model", &model[0][0]);
            shader.setMatrix4f("normalMat", &normal[0][0]);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
