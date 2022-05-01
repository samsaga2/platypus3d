#pragma once

#include "shader.h"
#include <GL/gl.h>

class gl_shader : public shader {
public:
    explicit gl_shader(const char* fname);
    ~gl_shader();

    void select() override;

private:
    GLuint id_;

    GLuint load_vertex(const char* vs_source);
    GLuint load_fragment(const char* fs_source);
    void create_shader(GLuint vs_id, GLuint fs_id);
};