#pragma once;
#include <core/types.hpp>
#include <core/classes/vkObject.h>

// using S_Object = SeewkObject&;

class SeewkObject
{
    int id;
    int width;
    int height;
    int x;
    int y;
    float borderRadius;
    Color color;
    int texture_id;
    VKObject vkObject;

public:
    SeewkObject() {}
    ~SeewkObject() {}
    Vec2 GetPosition()
    {
        return Vec2(x, y);
    }
    SeewkObject &SetPosition(Vec2 position)
    {
        x = position.x;
        y = position.y;
        vkObject.material.pos = Vec2(x, y);
        return *this;
    }
    Vec2 GetSize()
    {
        return Vec2(width, height);
    }
    SeewkObject &SetSize(Vec2 size)
    {
        width = size.x;
        height = size.y;
        vkObject.material.size = Vec2(width, height);
        return *this;
    }
    Color GetColor()
    {
        return color;
    }
    SeewkObject &SetColor(Color c)
    {
        color = c;
        vkObject.material.color = color;
        return *this;
    }
    float GetBorderRadius()
    {
        return borderRadius;
    }
    SeewkObject &SetBorderRadius(float r)
    {
        borderRadius = r;
        vkObject.material.borderRadius = borderRadius;
        return *this;
    }
    VKObject &GetVK()
    {
        return vkObject;
    }
};

using SwkObject = SeewkObject &;