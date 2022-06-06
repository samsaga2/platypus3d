#pragma once

#include <GL/gl.h>
#include <GL/glext.h>
#include <glm/glm.hpp>

class uniform_block {
 public:
    explicit uniform_block(GLuint binding_point, GLsizeiptr size);

    void set_data(GLuint offset, float value);
    void set_data(GLuint offset, int value);
    void set_data(GLuint offset, const glm::vec3& value);
    void set_data(GLuint offset, const glm::mat4& value);
    void set_data(GLuint offset, GLsizeiptr size, const void* data);

    [[nodiscard]] auto binding_point() const { return binding_point_; };

 private:
    GLuint id_;
    GLuint binding_point_;
};
