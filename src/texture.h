#pragma once

#include <GL/gl.h>

class texture {
 public:
    explicit texture(const char* fname);
    ~texture();

    void select(unsigned int index);

 private:
    GLuint texture_;
};
