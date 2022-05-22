#pragma once

#include "shader.h"
#include <GL/gl.h>
#include <string_view>

class gl_shader : public shader {
public:
    explicit gl_shader(std::string_view fname);
    ~gl_shader();

    void select() override;
    void set_uniform(const char* name, const glm::vec3& value) override;
    void set_uniform(const char* name, const glm::mat4& value) override;
    void set_uniform(const char* name, float value) override;
    void set_uniform(const char* name, int value) override;

private:
    GLuint id_;

    GLuint load_vertex(const char* vs_source);
    GLuint load_fragment(const char* fs_source);
    void create_shader(GLuint vs_id, GLuint fs_id);
};
