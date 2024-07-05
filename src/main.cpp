#include <iostream>
#include <string>
#include <glad/glad.h> // this needs to be included before GLFW
#include <GLFW/glfw3.h>

#include "graphics/OpenGLPlatform.h"

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

    while (!renderer.shouldClose()) {
        // input
        processInput(renderer.window);

        // rendering code here
        renderer.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        // poll events and swap buffers
        renderer.pollAndSwap();
    }

    return 0;
}
