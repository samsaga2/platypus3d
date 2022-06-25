#include "material.h"
#include "util.h"

namespace fs = std::filesystem;

void material::set_texture(const std::shared_ptr<::texture>& texture,
                           size_t pos) {
    if (textures_.size() <= pos)
        textures_.resize(pos + 1);
    textures_[pos] = texture;
}

void material::set_shader(const std::shared_ptr<::shader>& shader) {
    assert(shader != nullptr);
    shader_ = shader;
    shader_->select();
}

void material::select() {
    // select the shader
    shader_->select();

    // select the textures
    for (auto i = 0U; i < textures_.size(); i++)
        if (textures_[i] != nullptr)
            textures_[i]->select(i);
}

void material::set_uniform_block(const char* name, int block_index) {
    if (shader_ == nullptr) {
        std::cerr << "Cannot set uniform block, no shader loaded yet"
                  << std::endl;
        exit(1);
    }
    shader_->set_uniform_block(name, block_index);
}
