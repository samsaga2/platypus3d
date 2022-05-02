#pragma once

#include <GL/gl.h>
#include <vector>
#include "vertex_buffer.h"

class gl_indexed_vertex_buffer : public vertex_buffer {
public:
    explicit gl_indexed_vertex_buffer(const std::vector<float> &vertices,
                                      const std::vector<unsigned int> &indices);
    ~gl_indexed_vertex_buffer();

    void draw(const glm::mat4& m) override;

private:
    GLuint vbo_;
    GLuint vao_;
    GLuint ebo_;
};
