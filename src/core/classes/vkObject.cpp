#include <core/classes/vkObject.h>


void VKObject::Destroy(VkDevice device)
{
}

Object_OnClick VKObject::AddOnClick(std::function<void()> onClick)
{
    Object_OnClick objOnClick = {};
    objOnClick.id = id;
    objOnClick.callback = onClick;
    return objOnClick;
}
