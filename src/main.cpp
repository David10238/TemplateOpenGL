#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <glad/glad.h> // this needs to be included before GLFW
#include <GLFW/glfw3.h>

#include "graphics/OpenGLPlatform.h"
#include "graphics/Triangle.h"

void processInput(OpenGLPlatform &renderer) {
    GLFWwindow *window = renderer.window;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// todo get this out of top level
OpenGLPlatform renderer("OpenGlTemplate", 800, 600);

int main() {
    std::cout << renderer.GPU_NAME << "\n" << std::flush;

    const Triangle triangle1({
        1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,
    });

    const Triangle triangle2({
        -1.0f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -1.0f, -0.5f, 0.0f
    });

    glfwSetKeyCallback(renderer.window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
            renderer.toggleFullscreen();
            std::cout << "Toggled Fullscreen\n" << std::flush;
        }
    });

    while (!renderer.shouldClose()) {
        // input
        processInput(renderer);

        // rendering code here
        renderer.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        const float translation = fabsf(static_cast<float>(sin(glfwGetTime())));

        renderer.drawShape(triangle1, 1.0, 0.0, 1.0, 1.0);
        renderer.drawShape(triangle2.translate(translation, translation, 0.0), 1.0, 1.0, 1.0, 1.0);

        // poll events and swap buffers
        renderer.pollAndSwap();
    }

    return 0;
}
