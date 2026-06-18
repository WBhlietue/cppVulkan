#ifndef vkObject_h
#define vkObject_h

#include <vulkan/vulkan.h>
#include <functional>
#include <vector>
#include "objectActions.h"
#include "materialUBO.h"
#include "mesh.h"

static int vkObjectIdIncrease = 0;

struct VKObject
{
    Mesh mesh;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformMemory;
    MaterialUBO material;
    int id = vkObjectIdIncrease++;

    void Destroy(VkDevice device);
    void SetTexture(int textureID);

    Object_OnClick AddOnClick(std::function<void()> onClick);
};

#endif