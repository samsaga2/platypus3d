#pragma once

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

class vertex_buffer {
public:
    explicit vertex_buffer(const std::vector<vertex> &vertices);
    ~vertex_buffer();

    void draw();

private:
    GLuint vbo_;
    GLuint vao_;
    GLsizei size_;
};
