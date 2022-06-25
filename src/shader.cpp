#include "shader.h"
#include "util.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

shader::shader() { id_ = glCreateProgram(); }

shader::~shader() { glDeleteProgram(id_); }

void shader::load_vertex_shader(const std::string& fname) {
    auto vs_source = read_whole_file(fname.c_str());
    auto vs_id = load_vertex(vs_source.c_str());
    glAttachShader(id_, vs_id);
    glDeleteShader(vs_id);
    glLinkProgram(id_);
}

void shader::load_fragment_shader(const std::string& fname) {
    auto fs_source = read_whole_file(fname.c_str());
    auto fs_id = load_fragment(fs_source.c_str());
    glAttachShader(id_, fs_id);
    glDeleteShader(fs_id);
    glLinkProgram(id_);
}

void shader::select() { glUseProgram(id_); }

GLuint shader::load_vertex(const char* vs_source) {
    auto id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(id, 1, &vs_source, nullptr);
    glCompileShader(id);

    int success;
    char info[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: " << info << std::endl;
        exit(1);
    }

    return id;
}

GLuint shader::load_fragment(const char* fg_source) {
    auto id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(id, 1, &fg_source, NULL);
    glCompileShader(id);

    int success;
    char info[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: " << info << std::endl;
        exit(1);
    }

    return id;
}

void shader::set_uniform(const char* name, const glm::vec3& value) {
    auto loc = glGetUniformLocation(id_, name);
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

void shader::set_uniform(const char* name, const glm::mat4& value) {
    auto loc = glGetUniformLocation(id_, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_uniform(const char* name, float value) {
    auto loc = glGetUniformLocation(id_, name);
    glUniform1f(loc, value);
}

void shader::set_uniform(const char* name, int value) {
    auto loc = glGetUniformLocation(id_, name);
    glUniform1i(loc, value);
}

void shader::set_uniform_block(const char* name, int block_index) {
    auto index = glGetUniformBlockIndex(id_, name);
    glUniformBlockBinding(id_, index, block_index);
}
