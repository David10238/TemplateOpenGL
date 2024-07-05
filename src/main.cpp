#include <iostream>
#include <string>
#include <glad/glad.h> // this needs to be included before GLFW
#include <GLFW/glfw3.h>

#include "graphics/OpenGLPlatform.h"
#include "graphics/Shader.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    OpenGLPlatform renderer("OpenGlTemplate", 800, 600);

    std::cout << renderer.GPU_NAME << "\n" << std::flush;

    float vertices[] = {
        1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0,

        -1.0f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -1.0f, -0.5f, 0.0
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader myShader(RESOURCES_PATH "firstShader.vert", RESOURCES_PATH "firstShader.frag");

    // tell the vertex shader how to use the attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // setup a vertox attribute object

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    while (!renderer.shouldClose()) {
        // input
        processInput(renderer.window);

        // rendering code here
        renderer.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        myShader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // poll events and swap buffers
        renderer.pollAndSwap();
    }

    return 0;
}
