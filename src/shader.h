#pragma once

#include <GL/gl.h>

class shader {
public:
    explicit shader(const char* vertex_shader_source,
                    const char* fragment_shader_source);
    ~shader();

    void use();

private:
    GLuint shader_prog_;

    GLuint load_vertex(const char* vertex_shader_source);
    GLuint load_fragment(const char* fragment_shader_source);
    void create_shader(GLuint vertex_shader, GLuint fragment_shader);
};
