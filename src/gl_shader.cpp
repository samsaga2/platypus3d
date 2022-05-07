#include "gl_shader.h"
#include "util.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

gl_shader::gl_shader(const char* fname) {
    auto vs_fname = std::string{fname}+".vert";
    auto vs_source = read_whole_file(vs_fname.c_str());
    auto vs_id = load_vertex(vs_source.c_str());

    auto fs_fname = std::string{fname}+".frag";
    auto fs_source = read_whole_file(fs_fname.c_str());
    auto fs_id = load_fragment(fs_source.c_str());

    create_shader(vs_id, fs_id);
}

gl_shader::~gl_shader() {
    glDeleteProgram(id_);
}

void gl_shader::select() {
    glUseProgram(id_);
}

GLuint gl_shader::load_vertex(const char* vs_source) {
    auto id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(id, 1, &vs_source, nullptr);
    glCompileShader(id);

    int success;
    char info[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: "<< info << std::endl;
        exit(1);
    }

    return id;
}

GLuint gl_shader::load_fragment(const char* fg_source) {
    auto id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(id, 1, &fg_source, NULL);
    glCompileShader(id);

    int success;
    char info[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: "<< info << std::endl;
        exit(1);
    }

    return id;
}

void gl_shader::create_shader(GLuint vs_id, GLuint fg_id) {
    id_ = glCreateProgram();
    glAttachShader(id_, vs_id);
    glAttachShader(id_, fg_id);
    glLinkProgram(id_);
    glDeleteShader(vs_id);
    glDeleteShader(fg_id);

    // check for linking errors
    int success;
    char info[512];
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: "<< info << std::endl;
        exit(1);
    }
}

void gl_shader::set_uniform(const char* name, const glm::vec3& value) {
    auto loc = glGetUniformLocation(id_, name);
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

void gl_shader::set_uniform(const char* name, const glm::mat4& value) {
    auto loc = glGetUniformLocation(id_, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void gl_shader::set_uniform(const char* name, float value)  {
    auto loc = glGetUniformLocation(id_, name);
    glUniform1f(loc, value);
}

void gl_shader::set_uniform(const char* name, int value)  {
    auto loc = glGetUniformLocation(id_, name);
    glUniform1i(loc, value);
}
