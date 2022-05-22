#include "gl_render_factory.h"
#include "gl_render_device.h"
#include "gl_texture.h"
#include "gl_shader.h"
#include "gl_vertex_buffer.h"

auto gl_render_factory::create_device()
    -> std::shared_ptr<render_device>  {
    auto o = std::make_shared<gl_render_device>();
    return std::dynamic_pointer_cast<render_device>(o);
}

auto gl_render_factory::create_texture(std::string_view fname)
    -> std::shared_ptr<texture> {
    auto o = std::make_shared<gl_texture>(fname);
    return std::dynamic_pointer_cast<texture>(o);
}

auto gl_render_factory::create_shader(std::string_view fname)
    -> std::shared_ptr<shader> {
    auto o = std::make_shared<gl_shader>(fname);
    return std::dynamic_pointer_cast<shader>(o);
}

auto gl_render_factory::create_vertex_buffer(const std::vector<vertex> &vertices)
    -> std::shared_ptr<vertex_buffer> {
    auto o = std::make_shared<gl_vertex_buffer>(vertices);
    return std::dynamic_pointer_cast<vertex_buffer>(o);
}
