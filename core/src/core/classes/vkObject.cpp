#include <core/classes/vkObject.h>

void VKObject::Destroy(VkDevice device)
{
}

void VKObject::SetTexture(int textureID)
{
    material.textureID = textureID;
}


