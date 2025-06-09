#ifndef materialUBO_h
#define materialUBO_h

#include <glm/glm.hpp>

struct alignas(16) MaterialUBO
{
    glm::vec4 color;
    glm::vec2 pos;
    glm::vec2 size;
    float rotation;
    float borderRadius;
    float padding[3];
};

#endif