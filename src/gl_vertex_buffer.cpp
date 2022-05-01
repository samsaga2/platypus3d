#include "gl_vertex_buffer.h"
#include <glm/gtc/type_ptr.hpp>

gl_vertex_buffer::gl_vertex_buffer(const std::vector<float> &vertices,
                                   const std::vector<unsigned int> &indices) {
    // create vertex array object
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // create vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    // create element buffer object
    glGenBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // assign vertices to the shader location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // assign texcoords to the shader location 1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

gl_vertex_buffer::~gl_vertex_buffer() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}

void gl_vertex_buffer::draw(const glm::mat4& m) {
    // assign the matrix to the transform uniform of the current shader
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);
    auto loc = glGetUniformLocation(id, "transform");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));

    // draw the vertex buffer
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                                                 }
