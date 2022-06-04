#pragma once

#include <vector>
#include <filesystem>
#include <iostream>
#include <string_view>
#include "shader.h"
#include "texture.h"

class material {
public:
    void select();

    void load_material(const char *fname);

    void set_texture(const std::shared_ptr<::texture>& texture, size_t pos);
    void set_shader(const std::shared_ptr<::shader>& shader);

    template<typename T>
    void set_uniform(const char* name, const T& value) {
        // set uniform param of type vec3
        if(shader_ == nullptr) {
            std::cerr << "Cannot set uniform, no shader loaded yet" << std::endl;
            exit(1);
        }
        shader_->set_uniform(name, value);
    }

    void set_uniform_block(const char* name, int block_index);

private:
    std::vector<std::shared_ptr<texture>> textures_;
    std::shared_ptr<shader> shader_;
};
