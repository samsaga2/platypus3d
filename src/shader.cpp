#include "shader.h"
#include <iostream>
#include <stdexcept>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

shader::shader(const char* vertex_shader_source, const char *fragment_shader_source) {
    auto vertex_shader = load_vertex(vertex_shader_source);
    auto fragment_shader = load_fragment(fragment_shader_source);
    create_shader(vertex_shader, fragment_shader);
}

shader::~shader() {
    glDeleteProgram(shader_prog_);
}

void shader::use() {
    glUseProgram(shader_prog_);
}

GLuint shader::load_vertex(const char* vertex_shader_source) {
    auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    int success;
    char info[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, info);
            std::cerr << "Error compiling vertex shader: "<< info << std::endl;
            throw std::runtime_error(info);
        }

    return vertex_shader;
}

GLuint shader::load_fragment(const char* fragment_shader_source) {
    auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    int success;
    char info[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
        {
            glGetShaderInfoLog(fragment_shader, 512, NULL, info);
            std::cerr << "Error compiling vertex shader: "<< info << std::endl;
            throw std::runtime_error(info);
        }

    return fragment_shader;
}

void shader::create_shader(GLuint vertex_shader, GLuint fragment_shader) {
    shader_prog_ = glCreateProgram();
    glAttachShader(shader_prog_, vertex_shader);
    glAttachShader(shader_prog_, fragment_shader);
    glLinkProgram(shader_prog_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // check for linking errors
    int success;
    char info[512];
    glGetProgramiv(shader_prog_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_prog_, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: "<< info << std::endl;
        throw std::runtime_error(info);
    }
}