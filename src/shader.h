#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>

class shader {
public:
    explicit shader();
    ~shader();

    void load_vertex_shader(const std::string& fname);
    void load_fragment_shader(const std::string& fname);
    void select();

    void set_uniform(const char* name, const glm::vec3& value);
    void set_uniform(const char* name, const glm::mat4& value);
    void set_uniform(const char* name, float value);
    void set_uniform(const char* name, int value);
    void set_uniform_block(const char* name, int block_index);

private:
    GLuint id_;

    GLuint load_vertex(const char* vs_source);
    GLuint load_fragment(const char* fs_source);
};
