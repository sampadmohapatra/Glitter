#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setUniformi(const char* uniformName, std::vector<int> value);
    void setUniformf(const char* uniformName, std::vector<float> value);
    void setUniformui(const char* uniformName, std::vector<unsigned int> value);
    void setUniformMat4(const char* uniformName, std::vector<glm::mat4> value);

    // Activates the Shader Program
    void Activate() const;
    // Deletes the Shader Program
    void Delete() const;
private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int shader, const char* type) const;
};

#endif