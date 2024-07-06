#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <array>

class OpenGLPlatform;

class Triangle {
public:
    explicit Triangle(const std::array<float, 3 * 3> &vertices);

    std::array<float, 3 * 3> getVertices() const;

    Triangle translate(float x, float y, float z);

private:
    const std::array<float, 3 * 3> vertices;
};


#endif //TRIANGLE_H
