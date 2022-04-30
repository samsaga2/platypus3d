#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class transform {
 public:
    [[nodiscard]] auto position() const {
        return position_;
    }

    [[nodiscard]] auto orientation() const {
        return orientation_;
    }

    auto set_position(const glm::vec3& position) {
        position_ = position;
    }

    auto set_orientation(const glm::quat& orientation) {
        orientation_ = orientation;
    }

    [[nodiscard]] auto model_matrix() const {
        auto m = glm::mat4_cast(orientation_);
        m = m * glm::translate(m, position_);
        return m;
    }

 private:
    glm::vec3 position_;
    glm::quat orientation_;
};
