#include "texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture::texture(const char* fname) {
    // load image
    int width, height, channels;
    auto *data = stbi_load(fname, &width, &height, &channels, 0);
    if(data == nullptr) {
        std::cerr << "Error loading texture " << fname << std::endl;
        exit(1);
    }

    // create texture
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

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
    glDeleteTextures(1, &texture_);
}

void texture::select(unsigned int index) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture_);
}
