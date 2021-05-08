// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard C Headers
#include <cstdio>
#include <cstdlib>

// Standard C++ Headers
#include <iostream>

// Forward Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Data
float vertices[] {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};

float colors[] {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, 0.1f, 0.0f,  // bottom right
        0.2f, 0.3f, 0.4f,  // bottom left
        0.22f,  0.71f, 0.63f   // top left
};

unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (window == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create and bind buffers. Buffer data.
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    VBO1.Bind();
    VAO1.LinkAttrib(VBO1, 0, 3
                    , GL_FLOAT, 3*sizeof(float), (void*)0);

    VBO VBO2(colors, sizeof(colors));
    VBO2.Bind();
    VAO1.LinkAttrib(VBO2, 1, 3
                    , GL_FLOAT, 3*sizeof(float), (void*)0);

    EBO EBO1(indices, sizeof(indices));
    EBO1.Bind();

    VAO1.Unbind();
    VBO1.Unbind();
    VBO2.Unbind();
    EBO1.Unbind();

    // Create shaders and Link with shader program
    Shader shaderProgram("default.vert", "default.frag"
                          , R"(..\..\Glitter\Shaders\)");

    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        processInput(window);

        // Enable Shader Program
        shaderProgram.Activate();

        // Background Fill Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }   glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}