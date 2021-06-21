// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard C Headers
#include <cstdio>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h>

// Standard C++ Headers
#include <iostream>
#include <vector>

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

// anonymous namespace
// width and height are available
// only inside this file.
namespace {
    float viewportWidth, viewportHeight;
}

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    viewportWidth = WIDTH;
    viewportHeight = HEIGHT;
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

    // Circle vertices and colours with center (0,0,0) &
    // center's col (0.5,0.5,0.5). The center is used as the third
    // vertex/index while drawing the triangle that make up the circle.
    std::vector<float> circleVerts(3, 0.0f);
    circleVerts.push_back(0.5f);
    circleVerts.push_back(0.5f);
    circleVerts.push_back(0.5f);

    std::vector<unsigned int> circleIndices;

    float radius = 0.5f;
    float x, y;
    for(int theta=0; theta<360; theta+=5) {
        circleVerts.push_back(radius * cos(theta * M_PI /180.0));
        circleVerts.push_back(radius * sin(theta * M_PI /180.0));
        circleVerts.push_back(0.0f);
        x = *(circleVerts.rbegin()+2);
        y = *(circleVerts.rbegin()+1);
        circleVerts.push_back(abs(x));
        circleVerts.push_back(abs(y));
        circleVerts.push_back(sqrt(x*x+y*y));
    }

    int i;
    for(i=1; i<circleVerts.size()/6-1; i++) {
        circleIndices.push_back(0);
        circleIndices.push_back(i);
        circleIndices.push_back(i+1);
    }
    circleIndices.push_back(0);
    circleIndices.push_back(i);
    circleIndices.push_back(1);

    VBO VBO2(circleVerts.data(), sizeof(float)*circleVerts.size());
    VBO2.Bind();
    VAO1.LinkAttrib(VBO2, 3, 3, GL_FLOAT,               // circle verts
                    6 * sizeof(float), (void *) 0);
    VAO1.LinkAttrib(VBO2, 4, 3, GL_FLOAT,               // circle cols
                    6 * sizeof(float), (void *) (3 * sizeof(float)));
    EBO EBO2(circleIndices.data(), sizeof(unsigned int)*circleIndices.size());
    EBO2.Bind();

    // Create shaders and Link with shader program
    Shader shaderProgram("default.vert", "default.frag",
                         R"(..\..\Glitter\Shaders\)");

    // texture coordinates buffered in VBO
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
                    (void *) (6 * sizeof(float)));

    // textures
    // --------
    Texture texture1("container.jpg", GL_TEXTURE_2D, GL_RGB);
    Texture texture2("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);

    shaderProgram.setUniformf("mixFactor", {0.2});

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    glm::mat4 model, view, projection;

    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        processInput(window);

        // Background Fill Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Enable Shader Program
        shaderProgram.Activate();

        VAO1.Bind();


        shaderProgram.setUniformi("bDrawCircle", {false});
        texture1.Activate(GL_TEXTURE0);
        shaderProgram.setUniformi("texture1", {0});
        // Note: Below three transforms create projection * view * model.
        // Resulting matrix will be multiplied left multiplied with vertex coordinates
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.5, -0.5, 0.0));
        model = glm::rotate(model, glm::radians(-55.0f),
                              glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
        projection = glm::perspective(glm::radians(45.0f),
                              viewportWidth / viewportHeight, 0.1f, 100.0f);
        shaderProgram.setUniformMat4("model", {model});
        shaderProgram.setUniformMat4("view", {view});
        shaderProgram.setUniformMat4("projection", {projection});
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        texture2.Activate(GL_TEXTURE1);
        shaderProgram.setUniformi("texture1", {1});
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.5, 0.5, 0.0));
        model = glm::rotate(model, glm::radians(-55.0f),
                              glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
        shaderProgram.setUniformMat4("model", {model});
        shaderProgram.setUniformMat4("view", {view});
        shaderProgram.setUniformMat4("projection", {projection});
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        shaderProgram.setUniformi("bDrawCircle", {true});
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f),
                            glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
        shaderProgram.setUniformMat4("model", {model});
        shaderProgram.setUniformMat4("view", {view});
        shaderProgram.setUniformMat4("projection", {projection});
        glDrawElements( GL_TRIANGLES,
           circleIndices.size(), GL_UNSIGNED_INT, 0);

        VAO1.Unbind();

        // Flip Buffers and Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    viewportWidth = width;
    viewportHeight = height;
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}