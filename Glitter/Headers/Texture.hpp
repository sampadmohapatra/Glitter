#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "glad/glad.h"
#include "stb_image.h"

#include <iostream>

/*
 * GL_TEXTURE0 vs location number 0
 * GL_TEXTURE0 is not equal to 0 (uniform location), but both are connected.
 * Texture sampler2D with location 0 will draw data from texture
 * bound/activated to GL_TEXTURE0. There is no need to set texture unit num
 * while/before texture is created. It only needs to be set before a draw
 * call happens, e.g., glDrawElements().
 */

class Texture {
public:
    GLuint mID;
    GLenum mTexType;
    GLenum mTexUnitNum;

    /*
     * @imageName Texture image filename with location
     * @texType Texture type, e.g., GL_TEXTURE_1D, GL_TEXTURE_2D etc.
     * @imageFormat Input texture image format, e.g., GL_RGB, GL_RGBA
     * @texUnitEnum Texture unit to be used, e.g., GL_TEXTURE0, GL_TEXTURE1 etc.
     * @imageDataType Data type of input texture image, e.g., GL_UNSIGNED_BYTE
     */
    Texture(const char* imageName, GLenum texType, GLenum imageFormat
            , GLenum texUnitEnum = GL_TEXTURE0
            , GLenum imageDataType = GL_UNSIGNED_BYTE);

    // Activate Texture before draw call
    void activateTexture(GLuint texUnitEnum = GL_INVALID_VALUE);
    // Binds a texture
    void bindTexture() const;
    // Unbinds a texture
    void unbindTexture() const;
    // Deletes a texture
    void deleteTexture() const;
};
#endif