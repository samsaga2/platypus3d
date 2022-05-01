#include "material.h"
#include "util.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

void material::load_material(const char *fname) {
    auto base_path = fs::path{fname}.parent_path();

    auto f = std::ifstream(fname);
    for(std::string line; std::getline(f, line);) {
        // parse line command
        auto ss = std::stringstream{line};
        std::string command;
        ss >> command;

        if(command == "texture") {
            // append a new texture
            std::string arg0;
            ss >> arg0;
            textures_.emplace_back(load_texture((base_path / arg0).c_str()));
        } else if(command == "shader") {
            // load vertex and fragment shaders
            std::string arg;
            ss >> arg;
            shader_ = load_shader((base_path / arg).c_str());
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
