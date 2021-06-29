// Local Headers
#include "glitter.hpp"

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
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
// variables are available only inside this file.
namespace {
    float viewportWidth, viewportHeight;

    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrameTime = 0.0f; // Time of last frame

    Camera flyCam({0.0, 0.0, 3.0f});
    float lastX = WIDTH/2, lastY = HEIGHT/2;

    // bool to allow camera position to be set on first mouse click
    bool bFirstMouse = true;

    // light source
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
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

    // window position
    glfwSetWindowPos(window, 100, 50);

    // Hide and capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    // Show demo window ?
    bool show_demo_window = false;

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glEnable(GL_DEPTH_TEST);

    // Coordinate Axes
    VAO axesVAO;
    axesVAO.bindVAO();

    VBO axesVBO(axis, sizeof(axis));
    axesVAO.LinkAttrib(axesVBO, 0, 3, GL_FLOAT, 6 * sizeof(float),
                       (void *) 0);
    axesVAO.LinkAttrib(axesVBO, 1, 3, GL_FLOAT, 6 * sizeof(float),
                       (void *) (3 * sizeof(float)));

    axesVAO.unbindVAO();

    Shader drawCoordAxesShaderProg("xyz.vert", "xyz.frag",
                                   R"(..\..\Glitter\Shaders\)");

    // Cube Object
    VAO cubeVAO;
    cubeVAO.bindVAO();

    VBO cubeVBO(vertices, sizeof(vertices));
    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(float),
                       (void *) 0);
    cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 6 * sizeof(float),
                       (void *) (3 * sizeof(float)));
    cubeVAO.unbindVAO();


    Shader objShaderProg("default.vert", "default.frag",
                         R"(..\..\Glitter\Shaders\)");
    objShaderProg.setUniformVec("vObjectColor", {1.0f, 0.5f, 0.31f});
    objShaderProg.setUniformVec3("vLightPos", lightPos);
    objShaderProg.setUniformVec("vLightColor", {1.0f, 1.0f, 1.0f});

    // Light Source
    VAO lightVAO;
    lightVAO.bindVAO();

    // Using the cube VBO to represent the light source
    lightVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(float),
                        (void *) 0);

    lightVAO.unbindVAO();

    Shader lightShaderProg("lightSrc.vert", "lightSrc.frag",
                           R"(..\..\Glitter\Shaders\)");
    lightShaderProg.setUniformVec3("vLightPos", lightPos);

    glm::mat4 view, projection, model, normalMatrix;

    // Rendering Loop
    while (glfwWindowShouldClose(window) == false) {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // imgui Rendering
        ImGui::Render();

        // Update time diff since last frame draw
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput(window);

        // Background Fill Color
//        glClearColor((float)100/255, (float)38/255, (float)101/255, 1.0f);
        glClearColor(0.0, 0.0, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate view and projection matrices
        view = flyCam.getViewMatrix();
        projection = glm::perspective(glm::radians(flyCam.getFOV())
                ,viewportWidth / viewportHeight, 0.1f, 100.0f);

        // Draw the coordinate Axes
        drawCoordAxesShaderProg.activateShader();
        drawCoordAxesShaderProg.setUniformMat4("view", view);
        drawCoordAxesShaderProg.setUniformMat4("projection", projection);

        axesVAO.bindVAO();
        glDrawArrays( GL_LINE_STRIP, 0, 2);
        glDrawArrays( GL_LINE_STRIP, 2, 2);
        glDrawArrays( GL_LINE_STRIP, 4, 2);
        axesVAO.unbindVAO();

        // Draw Light
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.1f));

        lightShaderProg.activateShader();
        lightShaderProg.setUniformMat4("model", model);
        lightShaderProg.setUniformMat4("view", view);
        lightShaderProg.setUniformMat4("projection", projection);

        lightVAO.bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lightVAO.unbindVAO();

        // Draw Object
        objShaderProg.activateShader();

        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0, 0.0, -3.0));
//        model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.25f));
        normalMatrix = glm::transpose(glm::inverse(model));

        objShaderProg.setUniformMat4("view", view);
        objShaderProg.setUniformMat4("projection", projection);
        objShaderProg.setUniformMat4("model", model);
        objShaderProg.setUniformMat4("normalMatrix", normalMatrix);
        objShaderProg.setUniformVec3("vViewerPos", flyCam.mPosition);

        cubeVAO.bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeVAO.unbindVAO();

        // imgui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Flip Buffers and Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // imgui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // opengl cleanup
    cubeVBO.deleteVBO();
    axesVBO.deleteVBO();
    cubeVAO.deleteVAO();
    axesVAO.deleteVAO();
    lightVAO.deleteVAO();

    // glfw cleanup
    glfwDestroyWindow(window);
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