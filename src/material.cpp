#include "material.h"
#include "util.h"
#include "render_factory.h"
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

void material::set_texture(const std::shared_ptr<texture>& texture, size_t pos) {
    if(textures_.size() <= pos)
        textures_.resize(pos + 1);
    textures_[pos] = texture;
}

void material::set_shader(const std::shared_ptr<::shader>& shader) {
    assert(shader != nullptr);
    shader_ = shader;
    shader_->select();
}

void material::load_material(const char *fname, render_factory& factory) {
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
            auto texture = factory.create_texture((base_path / arg).string());
            set_texture(texture, tex_pos++);
        } else if(command == "shader") {
            std::string arg;
            ss >> arg;
            set_shader(factory.create_shader((base_path / arg).string()));
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
