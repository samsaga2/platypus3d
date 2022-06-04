#include "material.h"
#include "util.h"
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

void material::set_texture(const std::shared_ptr<::texture>& texture, size_t pos) {
    if(textures_.size() <= pos)
        textures_.resize(pos + 1);
    textures_[pos] = texture;
}

void material::set_shader(const std::shared_ptr<::shader>& shader) {
    assert(shader != nullptr);
    shader_ = shader;
    shader_->select();
}

void material::load_material(const char *fname) {
    auto base_path = fs::path{fname}.parent_path();

    auto tex_pos = 0U;
    auto f = std::ifstream(fname);
    for(std::string line; std::getline(f, line);) {
        // parse line command
        auto ss = std::stringstream{line};
        std::string command;
        ss >> command;

        // exec command
        if(command == "texture") {
            std::string arg;
            ss >> arg;
            auto texture = std::make_shared<::texture>((base_path / arg).string());
            set_texture(texture, tex_pos++);
        } else if(command == "shader") {
            std::string arg;
            ss >> arg;
            set_shader(std::make_shared<::shader>((base_path / arg).string()));
        } else if(command == "uniform_vec3") {
            std::string name;
            float x, y, z;
            ss >> name >> x >> y >> z;
            set_uniform(name.c_str(), glm::vec3{x, y, z});
        } else if(command == "uniform_float") {
            std::string name;
            float v;
            ss >> name >> v;
            set_uniform(name.c_str(), v);
        } else if(command == "uniform_int") {
            std::string name;
            int v;
            ss >> name >> v;
            set_uniform(name.c_str(), v);
        } else {
            std::cerr << "Unknown material command " << command << std::endl;
            exit(1);
        }
    }
}

void material::select() {
    // select the shader
    shader_->select();

    // select the textures
    for(auto i = 0U; i < textures_.size(); i++)
        if(textures_[i] != nullptr)
            textures_[i]->select(i);
}

void material::set_uniform_block(const char* name, int block_index) {
    if(shader_ == nullptr) {
        std::cerr << "Cannot set uniform block, no shader loaded yet" << std::endl;
        exit(1);
    }
    shader_->set_uniform_block(name, block_index);
}
