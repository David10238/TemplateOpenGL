#ifndef OPENGLPLATFORM_H
#define OPENGLPLATFORM_H

#include <glad/glad.h> // this needs to be included before GLFW
#include <GLFW/glfw3.h>

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

    void clearScreen(float read, float green, float blue, float alpha);

    void pollAndSwap();
};


#endif //OPENGLPLATFORM_H
