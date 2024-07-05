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

    // vertex shader

    const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // error handling
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << "\n" << std::flush;
    }

    // fragment shader
    const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;"
            "void main()"
            "{\n"
            "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // error handling
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << "\n" << std::flush;
    }

    // link the shaders

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // error handling
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    glUseProgram(shaderProgram);

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

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // poll events and swap buffers
        renderer.pollAndSwap();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;
}
