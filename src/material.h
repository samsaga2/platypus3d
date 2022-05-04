#pragma once

#include "render_factory.h"
#include <vector>
#include <filesystem>
#include <iostream>

class material {
public:
    explicit material(const char *fname, render_factory& factory);
    
    void select();

    void append_texture(const std::filesystem::path& fname);
    void load_shader(const std::filesystem::path& fname);

    template<typename T>
    void set_uniform(const char* name, const T& value) {
        // set uniform param of type vec3
        if(shader_ == nullptr) {
            std::cerr << "Cannot set uniform, no shader loaded yet" << std::endl;
            exit(1);
        }
        shader_->set_uniform(name, value);
    }

protected:
    void load_material(const char *fname);

private:
    render_factory& factory_;
    std::vector<std::shared_ptr<texture>> textures_;
    std::shared_ptr<::shader> shader_;

};
