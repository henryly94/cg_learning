#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>

#include <glm/glm.hpp>

#include "shader.h"

namespace cg_learning {

class Object {
public:
    Object(std::vector<float> vertices):vertices(vertices) {}
    std::vector<float> vertices;
    glm::mat4 model;
    const shader* shader;

    void scale(const glm::vec3& ratios);

    void transfer(const glm::vec3& delta);

    void rotate(const glm::vec3& angles);
};

} // namespace cg_learning

#endif // OBJECT_H_
