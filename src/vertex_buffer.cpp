#include "vertex_buffer.h"
#include "vertex_format.h"

vertex_buffer::vertex_buffer(const vertex_format& format,
                             const void* vertices_data, size_t vertices_count)
    : vertices_count_(vertices_count) {
    auto vertex_size = format.total_size() * sizeof(float);
    auto data_size = vertex_size * vertices_count;

    // create vertex array object
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // create vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, data_size, vertices_data, GL_STATIC_DRAW);

    auto offset = 0U;
    for (auto i = 0U; i < format.length(); i++) {
        auto element_size = format.element_size(i);
        glVertexAttribPointer(i, element_size, GL_FLOAT, GL_FALSE, vertex_size,
                              reinterpret_cast<void*>(offset));
        glEnableVertexAttribArray(i);
        offset += element_size * sizeof(float);
    }
}

vertex_buffer::~vertex_buffer() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void vertex_buffer::draw() {
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, vertices_count_);
}
