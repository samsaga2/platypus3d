#pragma once

#include "texture.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "render_device.h"
#include "vertex.h"
#include <memory>
#include <vector>
#include <string_view>

class render_factory {
 public:
    [[nodiscard]]  virtual auto create_device()
        -> std::shared_ptr<render_device> = 0;
    [[nodiscard]]  virtual auto create_texture(std::string_view fname)
        -> std::shared_ptr<texture> = 0;
    [[nodiscard]]  virtual auto create_shader(std::string_view fname)
        -> std::shared_ptr<shader> = 0;
    [[nodiscard]]  virtual auto create_vertex_buffer(const std::vector<vertex> &vertices)
        -> std::shared_ptr<vertex_buffer> = 0;
};
