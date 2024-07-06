#ifndef OPENGLPLATFORM_H
#define OPENGLPLATFORM_H

#include <memory>
#include <glad/glad.h> // this needs to be included before GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Triangle.h"

class OpenGLPlatform {
public:
    // fields
    GLFWwindow *window = nullptr;
    const char *GPU_NAME;

    // constructors and destructors
    OpenGLPlatform() = delete;

    OpenGLPlatform(const char *title, int width, int height);

    ~OpenGLPlatform();

    // methods
    [[nodiscard]] bool shouldClose() const;

    void clearScreen(float red, float green, float blue, float alpha);

    void drawShape(Triangle triangle, float red, float green, float blue, float alpha);

    void pollAndSwap();

private:
    void constructShaders();

    std::unique_ptr<Shader> triangleColorShader;
};


#endif //OPENGLPLATFORM_H
