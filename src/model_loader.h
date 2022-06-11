#pragma once

#include <vector>
#include <assimp/scene.h>
#include <filesystem>
#include <map>
#include "model.h"

class mesh;
class material;

class model_loader {
 public:
    auto load_model(std::string_view fname) -> model;

 private:
    struct vertex {
        float x;
        float y;
        float z;
        float u;
        float v;
        float r;
        float g;
        float b;
        float nx;
        float ny;
        float nz;
    };

    [[nodiscard]]
    auto deindex_vertices(const std::vector<vertex>& vertices,
                          const std::vector<unsigned int>& indices)
        const -> std::vector<vertex>;

    std::map<std::filesystem::path, std::shared_ptr<texture>> textures_;
    
    void process_node(std::vector<mesh>& meshes,
                      aiNode *node, const aiScene *scene,
                      const std::filesystem::path& base_path);

    [[nodiscard]]
    auto process_vertices(aiMesh *mesh) const
        -> std::shared_ptr<vertex_buffer>;

    void process_textures(material* mat, aiMaterial *scene_mat,
                          aiTextureType type,
                          const std::filesystem::path& base_path);

    [[nodiscard]]
    auto process_mesh(aiMesh *mesh, const aiScene *scene,
                      const std::filesystem::path& base_path)
        -> ::mesh;
};
