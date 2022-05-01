#include "gl_material.h"
#include "gl_texture.h"
#include "gl_shader.h"

gl_material::gl_material(const char *fname) {
    load_material(fname);
}

std::shared_ptr<texture> gl_material::load_texture(const char *fname) {
    auto t = std::make_shared<gl_texture>(fname);
    return std::dynamic_pointer_cast<texture>(t);
}

std::shared_ptr<shader> gl_material::load_shader(const char *fname)  {
    auto s = std::make_shared<gl_shader>(fname);
    return std::dynamic_pointer_cast<shader>(s);
}
