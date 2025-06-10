#ifndef vkObject_h
#define vkObject_h

#include <vulkan/vulkan.h>
#include <functional>
#include <vector>
#include "objectActions.h"
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

    Object_OnClick AddOnClick(std::function<void()> onClick);
};

#endif