#include "material.h"
#include "util.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

material::material(const char *fname) {
    load_material(fname);
}

void material::load_material(const char *fname) {
    auto base_path = fs::path{fname}.parent_path();

    auto f = std::ifstream(fname);
    for(std::string line; std::getline(f, line);) {
        auto ss = std::stringstream{line};
        std::string command;
        ss >> command;
        if(command == "texture") {
            std::string arg0;
            ss >> arg0;
            load_texture((base_path / arg0).c_str());
        } else if(command == "shader") {
            std::string arg0, arg1;
            ss >> arg0 >> arg1;
            load_shader((base_path / arg0).c_str(), (base_path / arg1).c_str());
        }
    }
}

void material::use() {
    texture_->use();
    shader_->use();
}

void material::load_texture(const char *fname) {
    texture_ = std::make_unique<texture>(fname);
}

void material::load_shader(const char *vert_fname, const char* frag_fname) {
    auto vert_source = read_whole_file(vert_fname);
    auto frag_source = read_whole_file(frag_fname);
    shader_ = std::make_unique<shader>(vert_source.c_str(), frag_source.c_str());
}
