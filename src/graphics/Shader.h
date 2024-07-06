#ifndef SHADER_H
#define SHADER_H

#include <string>

struct Shader {
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath);

    // for activation
    void use() const;

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setFloat4(const std::string &name, float v0, float v1, float v2, float v3) const;
};

#endif //SHADER_H
