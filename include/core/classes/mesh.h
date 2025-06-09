#ifndef mesh_h
#define mesh_h

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>

#include "vertex.h"

struct Mesh
{
    VkBuffer vBuffer;
    VkDeviceMemory vMemory;
    VkBuffer iBuffer;
    VkDeviceMemory iMemory;
    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;
};

#endif