#pragma once

#include "material.h"

class gl_material : public material {
 public:
    explicit gl_material(const char *fname);
    
 protected:
    std::shared_ptr<texture> load_texture(const char *fname) override;
    std::shared_ptr<shader> load_shader(const char *fname) override;
};
