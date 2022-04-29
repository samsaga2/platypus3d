#pragma once

#include <GL/gl.h>

class texture {
 public:
    explicit texture(const char* fname);
    ~texture();

    void use();

 private:
    GLuint texture_;
};
