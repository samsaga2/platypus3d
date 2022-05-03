#include "camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

camera::camera() {
    set_perspective(45.0f, 800/600.0f, 0.1f, 100.0f);
    update_vectors();
}

void camera::set_perspective(float fovy_degree, float aspect_ratio,
                             float z_near, float z_far) {
    projection_ = glm::perspective(glm::radians(fovy_degree),
                                   aspect_ratio, z_near, z_far);
}

auto camera::projection_matrix() const -> glm::mat4 {
    return projection_;
}

auto camera::view_matrix() const -> glm::mat4 {
    return glm::lookAt(position_, position_ + front_, up_);
}

void camera::set_position(const glm::vec3& position) {
    position_ = position;
}

void camera::set_world_up(const glm::vec3& world_up) {
    world_up_ = world_up;
    update_vectors();
}

void camera::set_yaw(float yaw) {
    yaw_ = glm::mod(yaw, 360.0f);
    update_vectors();
}

void camera::set_pitch(float pitch) {
    pitch_ = glm::mod(pitch, 360.0f);
    update_vectors();
}

void camera::update_vectors() {
    // calculate the new front vector
    front_.x = cosf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
    front_.y = sinf(glm::radians(pitch_));
    front_.z = sinf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
    front_ = glm::normalize(front_);

    // also re-calculate the right and up vector
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

void camera::look_at(const glm::vec3& v) {
    auto direction = glm::normalize(v - position_);
    yaw_   = glm::degrees(glm::atan(direction.z, direction.x));
    pitch_ = glm::degrees(glm::asin(direction.y));

    update_vectors();
}
