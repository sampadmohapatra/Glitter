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
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

// Axes Data      // Vertex Coord     // Vertex Col
float axis[] = {0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
                2.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                0.0f, 2.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 2.0f,   0.0f, 0.0f, 1.0f};

// Data
float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

// anonymous namespace
// width and height are available
// only inside this file.
namespace {
    float viewportWidth, viewportHeight;

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrameTime = 0.0f; // Time of last frame

    Camera flyCam;
    float lastX = WIDTH/2, lastY = HEIGHT/2;

    bool bFirstMouse = true;
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

    // Hide and capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glEnable(GL_DEPTH_TEST);

    // Create and bind buffers. Buffer data.
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    VBO1.Bind();
    // vertex coordinates buffered in VBO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float),
                    (void *) 0);

    // Create shaders and Link with shader program
    Shader shaderProg("default.vert", "default.frag",
                      R"(..\..\Glitter\Shaders\)");

    // texture coordinates buffered in VBO
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float),
                    (void *) (3 * sizeof(float)));

    // textures
    // --------
    Texture texture1("container.jpg", GL_TEXTURE_2D, GL_RGB);
    Texture texture2("awesomeface.png", GL_TEXTURE_2D, GL_RGBA);

    VAO1.Unbind();
    VBO1.Unbind();

    // Coordinate Axes
    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(axis, sizeof(axis));
    VBO2.Bind();

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float),
                    (void *) 0);
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float),
                    (void *) (3 * sizeof(float)));
    Shader drawCoordAxesShaderProg("xyz.vert", "xyz.frag",
                                   R"(..\..\Glitter\Shaders\)");

    VAO2.Unbind();
    VBO2.Unbind();

    glm::mat4 view, projection, model;

    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        // Update time diff since last frame draw
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput(window);

        // Background Fill Color
        glClearColor((float)100/255, (float)38/255, (float)101/255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = flyCam.getViewMatrix();
        projection = glm::perspective(glm::radians(flyCam.getFOV())
                ,viewportWidth / viewportHeight, 0.1f, 100.0f);

        // Draw the coordinate Axes
        drawCoordAxesShaderProg.Activate();
        VAO2.Bind();

        drawCoordAxesShaderProg.setUniformMat4("view", {view});
        drawCoordAxesShaderProg.setUniformMat4("projection", {projection});
        glDrawArrays( GL_LINE_STRIP, 0, 2);
        glDrawArrays( GL_LINE_STRIP, 2, 2);
        glDrawArrays( GL_LINE_STRIP, 4, 2);

        VAO2.Unbind();

        // Enable Shader Program
        shaderProg.Activate();

        VAO1.Bind();

        texture1.Activate(GL_TEXTURE0);
        shaderProg.setUniformi("sqTex1", {0});
        texture2.Activate(GL_TEXTURE1);
        shaderProg.setUniformi("sqTex2", {1});

        shaderProg.setUniformMat4("view", {view});
        shaderProg.setUniformMat4("projection", {projection});

        for(auto& pos:cubePositions) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pos);
            model = glm::rotate(model, currentFrameTime,
                                glm::vec3(0.5f, 1.0f, 0.0f));
            shaderProg.setUniformMat4("model", {model});
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        VAO1.Unbind();

        // Flip Buffers and Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    viewportWidth = width;
    viewportHeight = height;
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Check and update Camera position/rotation
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        flyCam.processKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        flyCam.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        flyCam.processKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        flyCam.processKeyboard(CameraMovement::RIGHT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
    if (bFirstMouse) { // initially set to true
        lastX = xPos;
        lastY = yPos;
        bFirstMouse = false;
    }

    float xOffset = xPos - lastX;
    // reversed since y-coordinates range from bottom to top
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    flyCam.processMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    flyCam.processMouseScroll(yOffset);
}