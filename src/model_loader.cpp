#include "model_loader.h"
#include "mesh.h"
#include "material.h"
#include "vertex_buffer.h"
#include "vertex_format.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

namespace fs = std::filesystem;

auto model_loader::load_model(std::string_view fname) -> model {
    auto import = Assimp::Importer{};
    auto* scene = import.ReadFile(std::string(fname).c_str(),
                                  aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        exit(1);
    }

    auto base_path = fs::path{fname}.parent_path();
    auto meshes = std::vector<mesh>{};
    process_node(meshes, scene->mRootNode, scene, base_path);

    return model(std::move(meshes));
}

void model_loader::process_node(std::vector<mesh>& meshes, aiNode *node, const aiScene *scene, const fs::path& base_path) {
    // process all the node's meshes (if any)
    for(auto i = 0U; i < node->mNumMeshes; i++)
    {
        auto *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplace_back(process_mesh(mesh, scene, base_path));
    }

    // then do the same for each of its children
    for(auto i = 0U; i < node->mNumChildren; i++)
        process_node(meshes, node->mChildren[i], scene, base_path);
}

auto model_loader::process_vertices(aiMesh *mesh) const
    -> std::shared_ptr<vertex_buffer> {
    auto vertices = std::vector<vertex>{};
    for(auto i = 0U; i < mesh->mNumVertices; i++) {
        auto v = vertex{};

        // pos
        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;

        // color
        if(mesh->HasVertexColors(0)) {
            v.r = mesh->mColors[0][i].r;
            v.g = mesh->mColors[0][i].g;
            v.b = mesh->mColors[0][i].b;
        } else {
            v.r = 1.0;
            v.g = 1.0;
            v.b = 1.0;
        }

        // normal
        if (mesh->HasNormals()) {
            v.nx = mesh->mNormals[i].x;
            v.ny = mesh->mNormals[i].y;
            v.nz = mesh->mNormals[i].z;
        } else {
            std::cerr << "missing normals" << std::endl;
            exit(1);
        }

        // texcoords
        if(mesh->HasTextureCoords(0)) {
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

    auto format = vertex_format{};
    format.add_element(vertex_element::position);
    format.add_element(vertex_element::texcoord);
    format.add_element(vertex_element::colors);
    format.add_element(vertex_element::normals);

    auto vertices_deindexed = deindex_vertices(vertices, indices);

    return std::make_shared<vertex_buffer>(format, vertices_deindexed.data(), vertices_deindexed.size());
}

auto model_loader::process_mesh(aiMesh *mesh, const aiScene *scene,
                                const fs::path& base_path)
    -> ::mesh {
    auto vertices = process_vertices(mesh);

    // material
    auto material = std::make_shared<::material>();
    material->set_shader(std::make_shared<shader>("../res/standard"));

    // textures
    auto* scene_material = scene->mMaterials[mesh->mMaterialIndex];
    process_textures(material.get(), scene_material, aiTextureType_DIFFUSE, base_path);
    process_textures(material.get(), scene_material, aiTextureType_SPECULAR, base_path);
    /* process_textures(material.get(), scene_material, aiTextureType_HEIGHT, base_path); */
    /* process_textures(material.get(), scene_material, aiTextureType_AMBIENT, base_path); */

    return ::mesh(vertices, material);
}

auto model_loader::process_textures(::material* mat, aiMaterial *scene_mat,
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
            texture = std::make_shared<::texture>(full_name.string());
            textures_.emplace(full_name, texture);
        }
        mat->set_texture(texture, tex_pos);
    }
}

auto model_loader::deindex_vertices(const std::vector<vertex>& vertices,
                                    const std::vector<unsigned int>& indices)
    const -> std::vector<vertex> {
    auto vertices_deindexed = std::vector<vertex>{};
    for(auto i = 0U; i < indices.size(); i+= 3U) {
        auto& v1 = vertices[indices[i+0]];
        auto& v2 = vertices[indices[i+1]];
        auto& v3 = vertices[indices[i+2]];
        vertices_deindexed.emplace_back(v1);
        vertices_deindexed.emplace_back(v2);
        vertices_deindexed.emplace_back(v3);
    }
    return vertices_deindexed;
}
