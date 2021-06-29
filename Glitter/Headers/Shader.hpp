#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

std::string getFileContents(const char* fileName, std::string relPath);

class Shader {
public:
    // Reference ID of the Shader Program
    GLuint mID;
    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char* vertexFile, const char* fragmentFile,
           const char* relPath="");

    // Set a Uniform in the Shader Program
    void setUniformi(const char* uniformName, std::vector<int> value);
    void setUniformf(const char* uniformName, std::vector<float> value);
    void setUniformui(const char* uniformName, std::vector<unsigned int> value);
    void setUniformVec(const char* uniformName, std::vector<float> value);
    void setUniformVec3(const char* uniformName, glm::vec3& value);
    void setUniformMat4(const char* uniformName, glm::mat4& value);

    // Activates the Shader Program
    void activateShader() const;
    // Deletes the Shader Program
    void deleteShader() const;
private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int shader, const char* type) const;
};

#endif