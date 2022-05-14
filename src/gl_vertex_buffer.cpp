#include "gl_vertex_buffer.h"

gl_vertex_buffer::gl_vertex_buffer(const std::vector<vertex> &vertices) : size_(vertices.size()) {
    // create vertex array object
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // create vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex),
                 vertices.data(), GL_STATIC_DRAW);

    // assign vertices to the shader location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glEnableVertexAttribArray(0);

    // assign texcoords to the shader location 1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // assign colors to the shader location 2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // assign normals to the shader location 3
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
}

gl_vertex_buffer::~gl_vertex_buffer() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void gl_vertex_buffer::draw() {
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, size_);
}
