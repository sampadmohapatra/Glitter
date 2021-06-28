#include "Texture.hpp"

Texture::Texture(const char* imageName, GLenum texType, GLenum imageFormat,
                 GLenum texUnitEnum, GLenum imageDataType) {
    // Assigns the type of the texture to the texture object
    mTexType = texType;
    // Store texture unit number to be used
    mTexUnitNum = texUnitEnum;

    // Stores the width, height, and the number of color channels of the image
    int imgWidth, imgHeight, numColChnls;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    unsigned char* imgBytes = stbi_load(imageName, &imgWidth, &imgHeight,
                                        &numColChnls, 0);

    if (!imgBytes) {
        std::cout << "Failed to load texture: " << imageName << std::endl;
    }

    // Generates an OpenGL texture object
    glGenTextures(1, &mID);

    // Activate texture
    activateTexture();

    // Configures the type of algorithm that is used to make the image
    // smaller or bigger
    glTexParameteri(mTexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(mTexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(mTexType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(mTexType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(mTexType, 0, GL_RGBA, imgWidth, imgHeight, 0,
                 imageFormat, imageDataType, imgBytes);
    // Generates MipMaps
    glGenerateMipmap(mTexType);

    // Deletes the image data as it is already stored in the OpenGL
    // texture object
    stbi_image_free(imgBytes);

    // Unbinds the OpenGL Texture object so that it can't
    // accidentally be modified
    glBindTexture(mTexType, 0);
}

void Texture::activateTexture(const GLuint texUnitEnum) {
    if(texUnitEnum != GL_INVALID_VALUE){
        mTexUnitNum = texUnitEnum;
    }
    glActiveTexture(mTexUnitNum);
    glBindTexture(mTexType, mID);
}

void Texture::bindTexture() const {
    glBindTexture(mTexType, mID);
}

void Texture::unbindTexture() const {
    glBindTexture(mTexType, 0);
}

void Texture::deleteTexture() const {
    glDeleteTextures(1, &mID);
}