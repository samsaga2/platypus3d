#include "texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture::texture(std::string_view fname) {
    // load image
    int width, height, channels;
    auto *data = stbi_load(std::string(fname).c_str(), &width, &height, &channels, 0);
    if(data == nullptr) {
        std::cerr << "Error loading texture " << fname << std::endl;
        exit(1);
    }

    // create texture
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    // texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // bind data
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGB, width, height, 0,
                 channels == 4 ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free image
    stbi_image_free(data);
}

texture::~texture() {
    glDeleteTextures(1, &id_);
}

void texture::select(unsigned int slot_index) {
    // bind the texture
    glActiveTexture(GL_TEXTURE0 + slot_index);
    glBindTexture(GL_TEXTURE_2D, id_);

    // notify to the shader in what slot is the texture
    GLint shader_id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shader_id);

    auto uniform_texture = std::string("texture") + std::to_string(slot_index);
    auto loc = glGetUniformLocation(shader_id, uniform_texture.c_str());
    glUniform1i(loc, slot_index);
}
