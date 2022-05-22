#pragma once

#include <vector>
#include <assimp/scene.h>
#include <filesystem>
#include <map>
#include "mesh.h"
#include "model.h"
#include "material.h"

class render_factory;
class texture;

class model_loader {
 public:
    explicit model_loader(render_factory& factory);

    auto load_model(std::string_view fname) -> model;

 private:
    render_factory& factory_;
    std::map<std::filesystem::path, std::shared_ptr<texture>> textures_;
    
    void process_node(std::vector<mesh>& meshes,
                      aiNode *node, const aiScene *scene,
                      const std::filesystem::path& base_path);

    [[nodiscard]]
    auto process_vertices(aiMesh *mesh) const
        -> std::shared_ptr<::vertex_buffer>;
    void process_textures(::material* mat, aiMaterial *scene_mat,
                          aiTextureType type,
                          const std::filesystem::path& base_path);

    [[nodiscard]]
    auto process_mesh(aiMesh *mesh, const aiScene *scene,
                      const std::filesystem::path& base_path)
        -> ::mesh;
};
