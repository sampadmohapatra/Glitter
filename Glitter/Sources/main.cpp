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
        // Vertex Coord          Color              Texture Coord
        -0.5f, -0.5f, 0.0f,   0.2f,  0.2f, 0.0f,     0.0f, 0.0f,  // Lower left corner
        -0.5f,  0.5f, 0.0f,   0.2f, 0.1f, 0.0f,      0.0f, 1.0f,  // Upper left corner
        0.5f,  0.5f, 0.0f,    0.2f, 0.3f, 0.4f,      1.0f, 1.0f,  // Upper right corner
        0.5f, -0.5f, 0.0f,    0.2f,  0.31f, 0.33f,  1.0f, 0.0f   // Lower right corner
};

unsigned int indices[] = {  // note that we start from 0!
        0, 2, 1,   // Upper triangle
        0, 3, 2   // Lower triangle
};

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL",
                                   nullptr, nullptr);

    // Check for Valid Context
    if (window == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create and bind buffers. Buffer data.
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    VBO1.Bind();
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT,
                    8 * sizeof(float), (void *) 0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT,
                    8 * sizeof(float), (void *) (3 * sizeof(float)));

    EBO EBO1(indices, sizeof(indices));
    EBO1.Bind();

    // Create shaders and Link with shader program
    Shader shaderProgram("default.vert", "default.frag",
                         R"(..\..\Glitter\Shaders\)");

    // texture coordinates buffered in VBO
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
                    (void *) (6 * sizeof(float)));

    // textures
    // --------
    Texture texture1("container.jpg", GL_TEXTURE_2D, GL_RGB);
    shaderProgram.setUniform<int>("texture1", {0});
    Texture texture2("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);
    shaderProgram.setUniform<int>("texture2", {1});

    shaderProgram.setUniform<float>("mixFactor", {0.2});

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 translator, rotator, scaler;

    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        processInput(window);

        // Background Fill Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture1.Activate(GL_TEXTURE0);
        texture2.Activate(GL_TEXTURE1);

        // Enable Shader Program
        shaderProgram.Activate();

        VAO1.Bind();

        // Note: Below three transforms create T*R*S.
        // They haven't yet been applied to any matrix.
        translator = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
        rotator = glm::rotate(translator, (float)glfwGetTime(),
                              glm::vec3(0.0, 0.0, 1.0));
        scaler = glm::scale(rotator, glm::vec3(0.5, 0.5, 0.5));

        shaderProgram.setUniformMatrix4fv("transform", scaler);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        translator = glm::translate(trans, glm::vec3(-0.5, 0.5, 0.0));
        rotator = glm::rotate(translator, (float)glfwGetTime(),
                              glm::vec3(0.0, 0.0, 1.0));
        scaler = glm::scale(rotator, glm::vec3(0.5, 0.5, 0.5));
        shaderProgram.setUniformMatrix4fv("transform", scaler);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Flip Buffers and Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}