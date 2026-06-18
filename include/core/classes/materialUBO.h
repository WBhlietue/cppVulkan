#ifndef materialUBO_h
#define materialUBO_h

#include <glm/glm.hpp>

struct alignas(16) MaterialUBO
{
    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec2 pos = {0,0};
    glm::vec2 size = {100,100};
    float rotation = 0;
    float borderRadius = 0;
    float padding[3];
    int textureID = -1;
};

#endif