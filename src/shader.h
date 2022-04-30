#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>

class shader {
public:
    explicit shader(const char* vertex_shader_source,
                    const char* fragment_shader_source);
    ~shader();

    void set_uniform(const char* name, int value);
    void select();

private:
    GLuint id_;

    GLuint load_vertex(const char* vertex_shader_source);
    GLuint load_fragment(const char* fragment_shader_source);
    void create_shader(GLuint vertex_shader, GLuint fragment_shader);
};

