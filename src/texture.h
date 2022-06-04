#pragma once

#include <GL/gl.h>
#include <string_view>

class texture {
 public:
    explicit texture(std::string_view fname);
    ~texture();

    void select(unsigned int slot_index);

 private:
    GLuint id_;
};
