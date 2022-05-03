#pragma once

#include <glm/glm.hpp>

class camera {
 public:
    explicit camera();

    void set_perspective(float fovy_radians, float aspect_ratio,
                         float z_near, float z_far);
    
    [[nodiscard]] auto projection_matrix() const -> glm::mat4;
    [[nodiscard]] auto view_matrix() const -> glm::mat4;

    [[nodiscard]] auto position() const { return position_; }
    [[nodiscard]] auto front() const { return front_; }
    [[nodiscard]] auto up() const { return up_; }
    [[nodiscard]] auto right() const { return right_; }
    [[nodiscard]] auto world_up() const { return world_up_; }
    [[nodiscard]] auto yaw() const { return yaw_; }
    [[nodiscard]] auto pitch() const { return pitch_; }

    void set_position(const glm::vec3& position);
    void set_world_up(const glm::vec3& world_up);
    void set_yaw(float yaw);
    void set_pitch(float pitch);

    void look_at(const glm::vec3& v);

 private:
    glm::mat4 projection_;
    glm::vec3 position_{0.0f, 0.0f, 3.0f};
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_{0.0f, 1.0f, 0.0f};
    float yaw_{-90.0f};
    float pitch_{0.0f};

    void update_vectors();
};
