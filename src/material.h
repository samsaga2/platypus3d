#pragma once

#include "texture.h"
#include "shader.h"
#include <memory>
#include <vector>

class material {
public:
    void select();

protected:
    void load_material(const char *fname);

    [[nodiscard]] virtual std::shared_ptr<texture> load_texture(const char *fname) = 0;
    [[nodiscard]] virtual std::shared_ptr<shader> load_shader(const char *fname) = 0;

private:
    std::vector<std::shared_ptr<texture>> textures_;
    std::shared_ptr<::shader> shader_;
};
