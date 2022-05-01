#pragma once

#include "render_factory.h"
#include <vector>

class material {
public:
    explicit material(const char *fname, render_factory& factory);
    
    void select();

protected:
    void load_material(const char *fname);

    [[nodiscard]] std::shared_ptr<texture> load_texture(const char *fname);
    [[nodiscard]] std::shared_ptr<shader> load_shader(const char *fname);

private:
    render_factory& factory_;
    std::vector<std::shared_ptr<texture>> textures_;
    std::shared_ptr<::shader> shader_;
};
