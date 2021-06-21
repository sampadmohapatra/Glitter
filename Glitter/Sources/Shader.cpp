#include"Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename, std::string relpath) {
    std::string newfilename {filename};
    std::ifstream in((relpath+newfilename).c_str(), std::ios::binary);
    if (in)
    {
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
               const char* relpath) {
    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = get_file_contents(vertexFile, relpath);
    std::string fragmentCode = get_file_contents(fragmentFile, relpath);

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
    ID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(ID);
    // Checks if Shaders linked successfully
    compileErrors(ID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate() const {
    glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete() const {
    glDeleteProgram(ID);
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
    GLint uniformID = glGetUniformLocation(ID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    Activate();
    // Sets the value of the uniform
    glUniform1i(uniformID, value[0]);
}

void Shader::setUniformf(const char *uniformName, std::vector<float> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(ID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    Activate();
    // Sets the value of the uniform
    glUniform1f(uniformID, value[0]);
}

void Shader::setUniformui(const char *uniformName, std::vector<unsigned int> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(ID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    Activate();
    // Sets the value of the uniform
    glUniform1ui(uniformID, value[0]);
}

void Shader::setUniformMat4(const char *uniformName, std::vector<glm::mat4> value) {
    // Gets the location of the uniform
    GLint uniformID = glGetUniformLocation(ID, uniformName);
    // Shader needs to be activated before changing the value of a uniform
    Activate();
    // Sets the value of the uniform
    glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(value[0]));
}
