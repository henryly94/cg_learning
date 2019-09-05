#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

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

    void setFloat(const std::string& name, float value);

    void setVec4f(const std::string& name, std::array<float, 4> value);

    void setVec3f(const std::string& name, float x, float y, float z);

    void setVec3f(const std::string& name, glm::vec3 value);

    void setMatrix4f(const std::string& name, const GLfloat* value);
};

} // namespace cg_learning

#endif // SHADER_H_
