#pragma once

#include <GL/gl.h>
#include <vector>

class mesh {
public:
    explicit mesh(const std::vector<float> &vertices,
                  const std::vector<unsigned int> &indices);
    ~mesh();

    void draw();

private:
    GLuint vbo_;
    GLuint vao_;
    GLuint ebo_;
};
