#include "Triangle.h"

Triangle::Triangle(const std::array<float, 3 * 3> &vertices) : vertices(vertices) {
}

Triangle Triangle::translate(const float x, const float y, const float z) const {
    std::array vertices = {
        x, y, z,
        x, y, z,
        x, y, z
    };

    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = vertices[i] + this->vertices[i];
    }

    return Triangle(vertices);
}

std::array<float, 3 * 3> Triangle::getVertices() const {
    return vertices;
}
