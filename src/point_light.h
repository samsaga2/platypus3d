#pragma once

#include <glm/glm.hpp>

class point_light {
public:
    [[nodiscard]] auto position() const {
        return position_;
    }

    [[nodiscard]] auto ambient() const {
        return ambient_;
    }

    [[nodiscard]] auto diffuse() const {
        return diffuse_;
    }

    [[nodiscard]] auto specular() const {
        return specular_;
    }

    auto set_position(const glm::vec3& position) {
        position_ = position;
    }

    auto set_ambient(const glm::vec3& v) {
        ambient_ = v;
    }

    auto set_diffuse(const glm::vec3& v) {
        diffuse_ = v;
    }

    auto set_specular(const glm::vec3& v) {
        specular_ = v;
    }

private:
    glm::vec3 position_{0.0f, 0.0f, 0.0f};
    glm::vec3 ambient_{0.3f, 0.3f, 0.3f};
    glm::vec3 diffuse_{0.7f, 0.7f, 0.7f};
    glm::vec3 specular_{1.0f, 1.0f, 1.0f};
};
