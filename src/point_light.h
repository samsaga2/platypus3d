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

    [[nodiscard]] auto attenuation_constant() const {
        return constant_;
    }

    [[nodiscard]] auto attenuation_linear() const {
        return linear_;
    }

    [[nodiscard]] auto attenuation_quadratic() const {
        return quadratic_;
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

     auto set_attenuation_constant(float v) {
        constant_ = v;
    }

     auto set_attenuation_linear(float v) {
        linear_ = v;
    }

     auto set_attenuation_quadratic(float v) {
        quadratic_ = v;
    }

private:
    glm::vec3 position_{0.0f, 0.0f, 0.0f};
    glm::vec3 ambient_{0.3f, 0.3f, 0.3f};
    glm::vec3 diffuse_{0.7f, 0.7f, 0.7f};
    glm::vec3 specular_{1.0f, 1.0f, 1.0f};
    float constant_{1.0f};
    float linear_{0.09f};
    float quadratic_{0.032f};
};
