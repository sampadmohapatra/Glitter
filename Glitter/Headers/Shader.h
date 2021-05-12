#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>
#include <type_traits>

std::string get_file_contents(const char* filename, std::string relpath);

class Shader
{
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char* vertexFile, const char* fragmentFile,
           const char* relpath="");

    // Set a Uniform in the Shader Program
    // TODO Need to see how to implement for glUniform(n)fv()
    template <typename T>
    void setUniform(const char* uniformName, const std::vector<T> value);

    // Activates the Shader Program
    void Activate() const;
    // Deletes the Shader Program
    void Delete() const;
private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int shader, const char* type) const;
};

// Set a Uniform in the Shader Program
template <typename T>
void Shader::setUniform(const char* uniformName, const std::vector<T> value) {
    // Gets the location of the uniform
    GLuint uniformID = glGetUniformLocation(ID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    Activate();
    // Sets the value of the uniform
    if(std::is_same<T, int>::value) {
        if (value.size() == 1)
            glUniform1i(uniformID, value[0]);
    }
    else if(std::is_same<T, float>::value) {
        if (value.size() == 1)
            glUniform1f(uniformID, value[0]);
    }
}
#endif