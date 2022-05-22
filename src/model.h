#pragma once

#include <vector>
#include <assimp/scene.h>
#include <filesystem>
#include <map>
#include "mesh.h"
#include "material.h"

class render_factory;
class texture;

class model {
 public:
    explicit model(render_factory& factory, std::string_view fname);

    template<typename T>
    void set_uniform(const char* name, const T& value) {
        for(auto& mesh : meshes_){
            mesh.material()->select();
            mesh.material()->set_uniform(name, value);
        }
    }

    void draw();

 private:
    render_factory& factory_;
    std::vector<mesh> meshes_;
    std::map<std::filesystem::path, std::shared_ptr<texture>> textures_;
    
    void load_model(std::string_view fname);
    void process_node(aiNode *node, const aiScene *scene, const std::filesystem::path& base_path);
    [[nodiscard]] auto process_vertices(aiMesh *mesh) const
        -> std::shared_ptr<::vertex_buffer>;
    void process_textures(::material* mat, aiMaterial *scene_mat,
                          aiTextureType type, const std::filesystem::path& base_path);
    void process_mesh(aiMesh *mesh, const aiScene *scene, const std::filesystem::path& base_path);
};
