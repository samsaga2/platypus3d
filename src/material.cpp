#include "material.h"
#include "util.h"
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

material::material(const char *fname, render_factory& factory) : factory_(factory) {
    load_material(fname);
}

void material::append_texture(const fs::path& fname) {
    textures_.emplace_back(factory_.create_texture(fname.c_str()));
}

void material::load_shader(const fs::path& fname) {
    // load vertex and fragment shaders
    shader_ = factory_.create_shader(fname.c_str());
    shader_->select();
}

void material::load_material(const char *fname) {
    auto base_path = fs::path{fname}.parent_path();

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
            append_texture(base_path / arg);
        } else if(command == "shader") {
            std::string arg;
            ss >> arg;
            load_shader(base_path / arg);
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
        textures_[i]->select(i);
}
