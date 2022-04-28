#pragma once

#include <GL/gl.h>
#include <vector>

class model {
public:
    explicit model(const std::vector<float> &vertices,
                   const std::vector<unsigned int> &indices);
    ~model();

    void draw();

private:
    GLuint vbo_;
    GLuint vao_;
    GLuint ebo_;
};
