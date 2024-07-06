#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <glad/glad.h> // this needs to be included before GLFW
#include <GLFW/glfw3.h>

#include "graphics/OpenGLPlatform.h"
#include "graphics/Triangle.h"

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

    Triangle triangle1({
        1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,
    });

    Triangle triangle2({
        -1.0f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -1.0f, -0.5f, 0.0f
    });

    while (!renderer.shouldClose()) {
        // input
        processInput(renderer.window);

        // rendering code here
        renderer.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        float translation = fabsf(sin(glfwGetTime()));

        renderer.drawShape(triangle1, 1.0, 0.0, 1.0, 1.0);
        renderer.drawShape(triangle2.translate(translation, translation, 0.0), 1.0, 1.0, 1.0, 1.0);

        // poll events and swap buffers
        renderer.pollAndSwap();
    }

    return 0;
}
