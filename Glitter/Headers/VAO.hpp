#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glad/glad.h"
#include "VBO.hpp"

class VAO {
public:
    // ID reference for the Vertex Array Object
    GLuint mID;

    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO Attribute such as a position or color to the VAO
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents
            , GLenum type, GLsizeiptr stride, void* offset);
    // Binds the VAO
    void bindVAO();
    // Unbinds the VAO
    void unbindVAO();
    // Deletes the VAO
    void deleteVAO();
};

// Constructor that generates a VAO ID
VAO::VAO() {
    glGenVertexArrays(1, &mID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents,
                     GLenum type, GLsizeiptr stride, void* offset) {
    VBO.bindVBO();
    glVertexAttribPointer(layout, numComponents, type,
                          GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbindVBO();
}

// Binds the VAO
void VAO::bindVAO() {
    glBindVertexArray(mID);
}

// Unbinds the VAO
void VAO::unbindVAO() {
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::deleteVAO() {
    glDeleteVertexArrays(1, &mID);
}

#endif