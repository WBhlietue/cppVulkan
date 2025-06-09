#ifndef vertex_h
#define vertex_h

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include<array>

struct Vertex
{
    glm::vec2 pos;
    glm::vec2 uv;
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

#endif