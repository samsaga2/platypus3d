#include "gl_vertex_buffer.h"
#include <glm/gtc/type_ptr.hpp>

gl_vertex_buffer::gl_vertex_buffer(const std::vector<float> &vertices) : size_(vertices.size() / 5) {
    // create vertex array object
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // create vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    // assign vertices to the shader location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // assign texcoords to the shader location 1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // assign colors to the shader location 2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

gl_vertex_buffer::~gl_vertex_buffer() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void gl_vertex_buffer::draw(const glm::mat4& m) {
    // assign the matrix to the transform uniform of the current shader
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);
    auto loc = glGetUniformLocation(id, "transform");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));

    // draw the vertex buffer
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, size_);
}
