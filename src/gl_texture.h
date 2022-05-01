#pragma once

#include <GL/gl.h>
#include "texture.h"

class gl_texture : public texture {
 public:
    explicit gl_texture(const char* fname);
    ~gl_texture();

    void select(unsigned int slot_index) override;

 private:
    GLuint id_;
};
