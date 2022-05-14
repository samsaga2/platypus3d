#pragma once

#include <GL/gl.h>
#include <vector>
#include "vertex_buffer.h"
#include "vertex.h"

class gl_vertex_buffer : public vertex_buffer {
public:
    explicit gl_vertex_buffer(const std::vector<vertex> &vertices);
    ~gl_vertex_buffer();

    void draw() override;

private:
    GLuint vbo_;
    GLuint vao_;
    GLsizei size_;
};
