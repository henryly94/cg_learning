#include "shader.h"

#include <glog/logging.h>

namespace cg_learning {
namespace {

void checkShaderStatusMaybeFatal(unsigned int id, const std::string& type) {
  static char infoLog[1024];
  int success;
  if (type == "COMPILE") {
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(id, 1024, NULL, infoLog);
        LOG(FATAL) << infoLog;
    };
  } else if (type == "LINK") {
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(id, 1024, NULL, infoLog);
        LOG(FATAL) << infoLog;
    }
  }
}

} // namespace

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try {
      // 打开文件
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // 读取文件的缓冲内容到数据流中
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();       
      // 关闭文件处理器
      vShaderFile.close();
      fShaderFile.close();
      // 转换数据流到string
      vertexCode   = vShaderStream.str();
      fragmentCode = fShaderStream.str();     
  }
  catch(std::ifstream::failure e) {
      LOG(FATAL) << "Fail when reading shader file. " << e.what();
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();     
  unsigned int vertex, fragment;
  // 顶点着色器
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkShaderStatusMaybeFatal(vertex, "COMPILE");

  // 片段着色器也类似
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkShaderStatusMaybeFatal(fragment, "COMPILE");

  // 着色器程序
  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);

  // 打印连接错误（如果有的话）
  checkShaderStatusMaybeFatal(id, "LINK");

  // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
  glDeleteShader(vertex);
  glDeleteShader(fragment);  
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set4f(const std::string& name, std::array<float, 4> value) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), value[0], value[1], value[2],value[3]);
}

void Shader::setMatrix4f(const std::string& name, const GLfloat* value) {
    int modelLoc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value);
}

} // namespace cg_learning
