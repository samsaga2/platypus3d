#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <memory>

class vertex_buffer;
class material;

class mesh {
 public:
    explicit mesh(std::shared_ptr<::vertex_buffer> vertex_buffer,
                  std::shared_ptr<::material> material);

    [[nodiscard]] auto vertex_buffer() const { return vertex_buffer_; }
    [[nodiscard]] auto material() const { return material_;}

    void draw();

 private:
    std::shared_ptr<::vertex_buffer> vertex_buffer_;
    std::shared_ptr<::material> material_;
};
