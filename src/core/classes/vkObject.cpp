#include <core/classes/vkObject.h>

void VKObject::Destroy(VkDevice device)
{
}

void VKObject::SetTexture(int textureID)
{
    material.textureID = textureID;
}

Object_OnClick VKObject::AddOnClick(std::function<void()> onClick)
{
    Object_OnClick objOnClick = {};
    objOnClick.id = id;
    objOnClick.callback = onClick;
    return objOnClick;
}
