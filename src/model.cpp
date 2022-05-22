#include "model.h"
#include "render_factory.h"
#include "texture.h"
#include "mesh.h"
#include "material.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <memory>

namespace fs = std::filesystem;

model::model(render_factory& factory, std::string_view fname) : factory_(factory) {
    load_model(fname);
}

void model::load_model(std::string_view fname) {
    auto import = Assimp::Importer{};
    auto* scene = import.ReadFile(std::string(fname).c_str(),
                                  aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        exit(1);
    }

    auto base_path = fs::path{fname}.parent_path();
    process_node(scene->mRootNode, scene, base_path);
}

void model::process_node(aiNode *node, const aiScene *scene, const fs::path& base_path) {
    // process all the node's meshes (if any)
    for(auto i = 0U; i < node->mNumMeshes; i++)
    {
        auto *mesh = scene->mMeshes[node->mMeshes[i]];
        process_mesh(mesh, scene, base_path);
    }

    // then do the same for each of its children
    for(auto i = 0U; i < node->mNumChildren; i++)
        process_node(node->mChildren[i], scene, base_path);
}

auto model::process_vertices(aiMesh *mesh) const -> std::shared_ptr<::vertex_buffer> {
    auto vertices = std::vector<vertex>{};
    for(auto i = 0U; i < mesh->mNumVertices; i++) {
        auto v = vertex{};

        // pos
        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;

        // color
        v.r = v.g = v.b = 1.0;

        // normal
        if (mesh->HasNormals()) {
            v.nx = mesh->mNormals[i].x;
            v.ny = mesh->mNormals[i].y;
            v.nz = mesh->mNormals[i].z;
        } else {
            auto normal = glm::vec3{v.x, v.y, v.z};
            normal /= normal.length();
            v.nx = normal.x;
            v.nx = normal.y;
            v.nx = normal.z;
        }

        // texcoords
        if(mesh->mTextureCoords[0]) {
            v.u = mesh->mTextureCoords[0][i].x;
            v.v = 1.0-mesh->mTextureCoords[0][i].y;
        } else {
            v.u = 0.0f;
            v.v = 0.0f;
        }

        vertices.emplace_back(v);
    }

    auto indices = std::vector<unsigned int>{};
    for(auto i = 0U; i < mesh->mNumFaces; i++) {
        auto& face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    auto vertices_deindexed = std::vector<vertex>{};
    for(auto i = 0U; i < indices.size(); i+= 3U) {
        auto& v1 = vertices[indices[i+0]];
        auto& v2 = vertices[indices[i+1]];
        auto& v3 = vertices[indices[i+2]];
        vertices_deindexed.emplace_back(v1);
        vertices_deindexed.emplace_back(v2);
        vertices_deindexed.emplace_back(v3);
    }

    return factory_.create_vertex_buffer(vertices_deindexed);
}

void model::process_mesh(aiMesh *mesh, const aiScene *scene, const fs::path& base_path) {
    auto vertices = process_vertices(mesh);

    // material
    auto material = std::make_shared<::material>();
    material->set_shader(factory_.create_shader("../res/standard"));

    auto* scene_material = scene->mMaterials[mesh->mMaterialIndex];
    process_textures(material.get(), scene_material, aiTextureType_DIFFUSE, base_path);
    process_textures(material.get(), scene_material, aiTextureType_SPECULAR, base_path);
    /* process_textures(material.get(), scene_material, aiTextureType_HEIGHT, base_path); */
    /* process_textures(material.get(), scene_material, aiTextureType_AMBIENT, base_path); */

    meshes_.emplace_back(::mesh(vertices, material));
}

auto model::process_textures(::material* mat, aiMaterial *scene_mat,
                             aiTextureType type, const fs::path& base_path)
    -> void {
    assert(mat != nullptr);
    assert(scene_mat != nullptr);

    auto tex_pos = 0U;
    switch(type) {
    case aiTextureType_DIFFUSE:
        tex_pos = 0;
        break;
    case aiTextureType_SPECULAR:
        tex_pos = 1;
        break;
    default:
        std::cerr << "texture type not implemented " << type << std::endl;
        exit(1);
    }
    
    if(scene_mat->GetTextureCount(type) > 0) {
        auto fname = aiString{};
        scene_mat->GetTexture(type, 0, &fname);

        auto texture = std::shared_ptr<::texture>();
        auto full_name = base_path / fname.C_Str();
        if(auto it = textures_.find(full_name); it != textures_.end()) {
            texture = it->second;
        } else {
            texture = factory_.create_texture(full_name.string());
            textures_.emplace(full_name, texture);
        }
        mat->set_texture(texture, tex_pos);
    }
}


void model::draw() {
    for(auto& mesh : meshes_) {
        mesh.material()->select();
        mesh.draw();
    }
}
