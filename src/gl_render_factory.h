#pragma once

#include "render_factory.h"

class gl_render_factory : public render_factory {
 public:
    auto create_device()
        -> std::shared_ptr<render_device> override;
    auto create_texture(const char *fname)
        -> std::shared_ptr<texture> override;
    auto create_shader(const char *fname)
        -> std::shared_ptr<shader> override;
    auto create_vertex_buffer(const std::vector<float> &vertices)
        -> std::shared_ptr<vertex_buffer> override;
    auto create_vertex_buffer(const std::vector<float> &vertices,
                              const std::vector<unsigned int> &indices)
        -> std::shared_ptr<vertex_buffer> override;
};
