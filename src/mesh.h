#ifndef MESH_H_
#define MESH_H_

#include "shader.h"

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace cg_learning {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};


class Mesh {
public:
    std::vector<Vertex> vertices_;
    std::vector<Texture> textures_;
    std::vector<unsigned int> indices_;

    Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices)
        :vertices_(vertices), textures_(textures), indices_(indices) {
        setupMesh();
    }

    void Draw(Shader& shader) const;

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

} // namespace cg_learning

#endif // MESH_H_
