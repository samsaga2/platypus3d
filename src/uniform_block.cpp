#include "uniform_block.h"
#include <cstdio>
#include <glm/gtc/type_ptr.hpp>

uniform_block::uniform_block(GLuint binding_point, GLsizeiptr size)
    : binding_point_(binding_point) {
    glGenBuffers(1, &id_);
    glBindBuffer(GL_UNIFORM_BUFFER, id_);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, binding_point, id_, 0, size);
}

void uniform_block::set_data(GLuint offset, float value) {
    set_data(offset, sizeof(value), &value);
}

void uniform_block::set_data(GLuint offset, int value) {
    set_data(offset, sizeof(value), &value);
}

void uniform_block::set_data(GLuint offset, const glm::vec3& value) {
    set_data(offset, sizeof(glm::vec3), glm::value_ptr(value));
}

void uniform_block::set_data(GLuint offset, const glm::mat4& value) {
    set_data(offset, sizeof(glm::mat4), glm::value_ptr(value));
}

void uniform_block::set_data(GLuint offset, GLsizeiptr size, const void* data) {
    glBindBuffer(GL_UNIFORM_BUFFER, id_);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
