#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glog/logging.h>
#include <gflags/gflags.h>
#include <stb_image.h>
#include <absl/strings/str_cat.h>
#include "shader.h"

DEFINE_int32(window_height, 800, "Initial window height.");
DEFINE_int32(window_width, 600, "Initial window width");
DEFINE_string(root_path, "../", "The path for project root.");
DEFINE_string(img_path, "resource/wood.jpg", "The path for img.");
DEFINE_string(shader_directory, "src/", "The path for shader files.");

using cg_learning::Shader;
using absl::StrCat;

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

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* orangeFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char* yellowFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.7f, 0.15f, 1.0f);\n"
    "}\n\0";

const char* uniformFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 outColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = outColor;\n"
    "}\n\0";

unsigned int GetShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); 

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG(FATAL) << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG(FATAL) << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG(FATAL) << "Shader program error: " << infoLog;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
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

    unsigned int texture;
    glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				
		int width, height, nrChannels;
		unsigned char *data = stbi_load(StrCat(FLAGS_root_path, FLAGS_img_path).c_str(), &width, &height, &nrChannels, 0);
		if (!data) {
			LOG(FATAL) << "Failed when loading image from " << FLAGS_img_path; 
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

    unsigned int orangeShaderProgram = GetShaderProgram(vertexShaderSource, orangeFragmentShaderSource);
    unsigned int yellowShaderProgram = GetShaderProgram(vertexShaderSource, yellowFragmentShaderSource);
    unsigned int uniformShaderProgram = GetShaderProgram(vertexShaderSource, uniformFragmentShaderSource);
    
    Shader uniformShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "uniform.fs"));
    Shader position2ColorShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "position.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple.fs"));
    Shader textureShader(StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple_texture.vs"), StrCat(FLAGS_root_path, FLAGS_shader_directory, "simple_texture.fs"));

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

        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        position2ColorShader.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        /*
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        uniformShader.use();
        uniformShader.setUniform4f("outColor", {0, greenValue, 0, 1.0f});
        */
        textureShader.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(unsigned int)));
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
     // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
