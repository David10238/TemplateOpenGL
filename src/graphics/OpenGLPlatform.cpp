#include "OpenGLPlatform.h"

#include <stdexcept>

#include "Triangle.h"

int OpenGLPlatform::width = 0;
int OpenGLPlatform::resetWidth = 0;
int OpenGLPlatform::height = 0;
int OpenGLPlatform::resetHeight = 0;
int OpenGLPlatform::resetX = 0;
int OpenGLPlatform::resetY = 0;

OpenGLPlatform::OpenGLPlatform(const char *title, const int width, const int height) {
    OpenGLPlatform::width = width;
    OpenGLPlatform::resetWidth = width;
    OpenGLPlatform::height = height;
    OpenGLPlatform::resetHeight = height;

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

    constructShaders();
}

void OpenGLPlatform::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    OpenGLPlatform::width = width;
    OpenGLPlatform::height = height;
}

OpenGLPlatform::~OpenGLPlatform() {
    glfwTerminate();
}

void OpenGLPlatform::constructShaders() {
    triangleColorShader = std::make_unique<Shader>(RESOURCES_PATH "shaders/triangle.vert",
                                                   RESOURCES_PATH "shaders/triangle.frag");
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

void OpenGLPlatform::toggleFullscreen() {
    fullscreen = !fullscreen;
    if (fullscreen) {
        glfwGetWindowPos(window, &resetX, &resetY);
        glfwGetWindowSize(window, &resetWidth, &resetHeight);

        GLFWmonitor *monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
    } else {
        glfwSetWindowMonitor(window, nullptr, resetX, resetY, resetWidth, resetHeight, 0);
    }
}

void OpenGLPlatform::setFullscreen(const bool fullscreen) {
    if (this->fullscreen != fullscreen) {
        toggleFullscreen();
    }
}

void OpenGLPlatform::drawShape(const Triangle &triangle, const float red, const float green, const float blue,
                               const float alpha) const {
    // todo setting up stuff might night need to be called often
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.getVertices()), triangle.getVertices().data(), GL_STATIC_DRAW);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.getVertices()), triangle.getVertices().data(), GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    // these lines have to be called every draw;
    triangleColorShader->use();
    triangleColorShader->setFloat4("MyColor", red, green, blue, alpha);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
