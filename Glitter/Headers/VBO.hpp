#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "glad/glad.h"

class VBO {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID;
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    VBO(GLfloat* vertices, GLsizeiptr size);
    VBO(GLdouble* vertices, GLsizeiptr size);

    // Binds the VBO
    void bindVBO();
    // Unbinds the VBO
    void unbindVBO();
    // Deletes the VBO
    void deleteVBO();
};

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::VBO(GLdouble* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::bindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::unbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::deleteVBO() {
    glDeleteBuffers(1, &ID);
}

#endif