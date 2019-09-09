#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace cg_learning {

class Model {
public:
    Model(const char* path);

    Model(const Model& model) = delete;
    Model& operator=(const Model& model) = delete;

    void Draw(Shader& shader);
private:
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                         std::string typeName);
};

} // namespace cg_learning

#endif // MODEL_H_
