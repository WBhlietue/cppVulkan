#ifndef vkObject_h
#define vkObject_h

#include <vulkan/vulkan.h>
#include <functional>
#include <vector>

#include "materialUBO.h"
#include "mesh.h"

struct VKObject
{
    Mesh mesh;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformMemory;
    MaterialUBO material;
    int id;

    void Destroy(VkDevice device);

    void AddOnClick(std::function<void()> onClick);
};

#endif