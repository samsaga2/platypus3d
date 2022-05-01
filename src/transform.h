#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    auto select() const {
        auto m = model_matrix();

        // assign the matrix to the transform uniform of the current shader
        GLint id;
        glGetIntegerv(GL_CURRENT_PROGRAM,&id);
        auto loc = glGetUniformLocation(id, "transform");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
    }

 private:
    glm::vec3 position_;
    glm::quat orientation_;
};
