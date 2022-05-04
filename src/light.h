#pragma once

#include <glm/glm.hpp>

class light {
 public:
    [[nodiscard]] auto position() const {
        return position_;
    }

    [[nodiscard]] auto color() const {
        return color_;
    }

    auto set_position(const glm::vec3& position) {
        position_ = position;
    }

    auto set_color(const glm::vec3& color) {
        color_ = color;
    }

 private:
    glm::vec3 position_{0.0f, 0.0f, 0.0f};
    glm::vec3 color_{1.0f, 1.0f, 1.0f};
};
