#include "transform.h"

auto transform::position() const -> glm::vec3 { return position_; }

auto transform::scale() const -> glm::vec3 { return scale_; }

auto transform::orientation() const -> glm::quat { return orientation_; }

auto transform::local_matrix() const -> glm::mat4 {
    auto m = glm::scale(glm::mat4(1.0f), scale_);
    m = glm::mat4_cast(orientation_) * m;
    return glm::translate(m, position_);
}

void transform::set_position(const glm::vec3& position) {
    position_ = position;
}

void transform::set_orientation(const glm::quat& orientation) {
    orientation_ = orientation;
}

void transform::set_scale(const glm::vec3& scale) { scale_ = scale; }

void transform::set_parent_matrix(const glm::mat4& m) { parent_matrix_ = m; }

auto transform::world_matrix() const -> glm::mat4 {
    return parent_matrix_ * local_matrix();
}
