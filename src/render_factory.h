#pragma once

#include "texture.h"
#include "shader.h"
#include "vertex_buffer.h"
#include <memory>
#include <vector>

class render_factory {
 public:
    [[nodiscard]]  virtual auto create_texture(const char *fname)
        -> std::shared_ptr<texture> = 0;
    [[nodiscard]]  virtual auto create_shader(const char *fname)
        -> std::shared_ptr<shader> = 0;
    [[nodiscard]]  virtual auto create_vertex_buffer(const std::vector<float> &vertices,
                                                     const std::vector<unsigned int> &indices)
        -> std::shared_ptr<vertex_buffer> = 0;
};
