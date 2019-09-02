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

DEFINE_int32(window_height, 600, "Initial window height.");
DEFINE_int32(window_width, 600, "Initial window width");
DEFINE_string(root_path, "../", "The path for project root.");
DEFINE_string(img_path, "resource/", "The path for img.");
DEFINE_string(shader_directory, "src/", "The path for shader files.");

using cg_learning::Shader;
using absl::StrCat;
using absl::StrSplit;

const float vertices[] = {
  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上角
  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下角
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// 左下角
  -0.5f, 0.5f, 0.0f, 0.3f, 0.7f, 0.2f, 0.0f, 1.0f   // 左上角
};
 
const unsigned int indices[] = { // 注意索引从0开始! 
  0, 1, 3, // 第一个三角形
  1, 2, 3  // 第二个三角形
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
}

void renderBackground() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Init(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int main(int argc, char** argv){
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

    unsigned int box_texture = GetTextureFromFile("wood.jpg");
    unsigned int face_texture = GetTextureFromFile("awesomeface.png");
    Shader uniformShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "uniform.fs"));
    Shader position2ColorShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "position.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple.fs"));
    Shader textureShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple_texture.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple_texture.fs"));
    Shader doubleTextureShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple_texture.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "double_texture.fs"));
  
    doubleTextureShader.use();
    glUniform1i(glGetUniformLocation(doubleTextureShader.id, "texture1"), 0);
    glUniform1i(glGetUniformLocation(doubleTextureShader.id, "texture2"), 1);
    glm::mat4 trans;
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    unsigned int transformLoc = glGetUniformLocation(doubleTextureShader.id, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

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

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while(!glfwWindowShouldClose(window)) {

        processInput(window);

        renderBackground();

        // Process transform
        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(doubleTextureShader.id, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, box_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, face_texture);

        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
     // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
