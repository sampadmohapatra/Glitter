#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
    // ID reference of Elements Buffer Object
    GLuint mID;
    // Constructor that generates a Elements Buffer Object and links it to indices
    EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void bindEBO();
    // Unbinds the EBO
    void unbindEBO();
    // Deletes the EBO
    void deleteEBO();
};

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size) {
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::bindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

// Unbinds the EBO
void EBO::unbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::deleteEBO() {
    glDeleteBuffers(1, &mID);
}
#endif