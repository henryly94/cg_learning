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
  
    void setUniform4f(const std::string& name, std::array<float, 4> value);
};

} // namespace cg_learning

#endif // SHADER_H_
