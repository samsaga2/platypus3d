#pragma once

#include "texture.h"
#include "shader.h"
#include <memory>
#include <vector>

class material {
 public:
    explicit material(const char *fname);

    void use();

 private:
    std::vector<std::unique_ptr<texture>> textures_;
    std::unique_ptr<shader> shader_;
    
    void load_material(const char *fname);
    void load_texture(const char *fname);
    void load_shader(const char *vert_fname, const char *frag_fname);
};
