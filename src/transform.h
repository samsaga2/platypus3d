#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class transform {
  public:
    [[nodiscard]] auto position() const -> glm::vec3;
    [[nodiscard]] auto scale() const -> glm::vec3;
    [[nodiscard]] auto orientation() const -> glm::quat;

    void set_position(const glm::vec3& position);
    void set_orientation(const glm::quat& orientation);
    void set_scale(const glm::vec3& scale);
    void set_parent_matrix(const glm::mat4& m);

    [[nodiscard]] auto local_matrix() const -> glm::mat4;
    [[nodiscard]] auto world_matrix() const -> glm::mat4;

  private:
    glm::vec3 position_{0.0f, 0.0f, 0.0f};
    glm::vec3 scale_{1.0f, 1.0f, 1.0f};
    glm::quat orientation_{0.0f, 0.0f, 0.0f, 0.0f};
    glm::mat4 parent_matrix_{1.0f};
};
