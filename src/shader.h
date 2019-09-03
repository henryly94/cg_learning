#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <array>

namespace cg_learning {

class Shader {
  public:

    unsigned int id;

    explicit Shader(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath);

    void use();
    
    void setInt(const std::string& name, int value);

    void set4f(const std::string& name, std::array<float, 4> value);

    void setVec3f(const std::string& name, std::array<float, 3> value);

    void setMatrix4f(const std::string& name, const GLfloat* value);
};

} // namespace cg_learning

#endif // SHADER_H_
