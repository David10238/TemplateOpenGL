#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <array>

class OpenGLPlatform;

class Triangle {
public:
    explicit Triangle(const std::array<float, 3 * 3> &vertices);

    [[nodiscard]] std::array<float, 3 * 3> getVertices() const;

    [[nodiscard]] Triangle translate(float x, float y, float z) const;

private:
    const std::array<float, 3 * 3> vertices;
};


#endif //TRIANGLE_H
