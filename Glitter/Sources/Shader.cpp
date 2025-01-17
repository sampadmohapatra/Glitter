#include "Shader.hpp"

// Reads a text file and outputs a string with everything in the text file
std::string getFileContents(const char* fileName, std::string relPath) {
    std::string newfilename {fileName};
    std::ifstream in((relPath+newfilename).c_str(), std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile,
               const char* relPath) {
    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = getFileContents(vertexFile, relPath);
    std::string fragmentCode = getFileContents(fragmentFile, relPath);

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);
    // Checks if Shader compiled successfully
    compileErrors(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);
    // Checks if Shader compiled successfully
    compileErrors(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference
    mID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(mID, vertexShader);
    glAttachShader(mID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(mID);
    // Checks if Shaders linked successfully
    compileErrors(mID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::activateShader() const {
    glUseProgram(mID);
}

// Deletes the Shader Program
void Shader::deleteShader() const {
    glDeleteProgram(mID);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type) const {
    // Stores status of compilation
    GLint hasCompiled;
    // Character array to store error message in
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type
                      << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type
                      << "\n" << infoLog << std::endl;
        }
    }
}

void Shader::setUniformi(const char *uniformName, std::vector<int> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(mID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    activateShader();
    // Sets the value of the uniform
    glUniform1i(uniformID, value[0]);
}

void Shader::setUniformf(const char *uniformName, std::vector<float> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(mID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    activateShader();
    // Sets the value of the uniform
    glUniform1f(uniformID, value[0]);
}

void Shader::setUniformui(const char *uniformName, std::vector<unsigned int> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(mID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    activateShader();
    // Sets the value of the uniform
    glUniform1ui(uniformID, value[0]);
}

void Shader::setUniformVec(const char* uniformName, std::vector<float> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(mID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    activateShader();
    // Sets the value of the uniform depending on length of vector
    switch(value.size()) {
        case 1:
            glUniform1fv( uniformID, 1, value.data());
            break;
        case 2:
            glUniform2fv( uniformID, 1, value.data());
            break;
        case 3:
            glUniform3fv( uniformID, 1, value.data());
            break;
        case 4:
            glUniform4fv( uniformID, 1, value.data());
            break;
    }
}

void Shader::setUniformVec3(const char* uniformName, glm::vec3& value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(mID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    activateShader();
    glUniform3fv( uniformID, 1, glm::value_ptr(value));
}

void Shader::setUniformMat4(const char *uniformName, glm::mat4& value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(mID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    activateShader();
    // Sets the value of the uniform
    glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(value));
}
