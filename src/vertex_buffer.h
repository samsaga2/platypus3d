#pragma once

#include <GL/gl.h>
#include <vector>
#include <cstddef>

class vertex_format;

class vertex_buffer {
public:
    explicit vertex_buffer(const vertex_format& format,
                           const void* vertices_data,
                           size_t vertices_count);
    ~vertex_buffer();
    
    void draw();

private:
    GLuint vbo_;
    GLuint vao_;
    GLsizei vertices_count_;
};
