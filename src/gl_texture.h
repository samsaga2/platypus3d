#pragma once

#include <GL/gl.h>
#include <string_view>
#include "texture.h"

class gl_texture : public texture {
 public:
    explicit gl_texture(std::string_view fname);
    ~gl_texture();

    void select(unsigned int slot_index) override;

 private:
    GLuint id_;
};
