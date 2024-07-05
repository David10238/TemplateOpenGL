#include "OpenGLPlatform.h"

#include <stdexcept>

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

OpenGLPlatform::OpenGLPlatform(const char *title, const int width, const int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // used for Mac OS X

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    GPU_NAME = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

OpenGLPlatform::~OpenGLPlatform() {
    glfwTerminate();
}


bool OpenGLPlatform::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void OpenGLPlatform::clearScreen(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLPlatform::pollAndSwap() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}
