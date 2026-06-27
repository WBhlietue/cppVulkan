#pragma once
#include <core/types.hpp>
#include <core/classes/vkObject.h>
#include <functional>

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
    std::function<void()> onMouseEnter = []() {};
    std::function<void()> onMouseExit = []() {};
    std::function<void()> onMouseStay = []() {};
    bool isMouseEnter = false;

public:
    SeewkObject() {}
    ~SeewkObject() {}
    void MouseEnter()
    {
        onMouseEnter();
    }
    void MouseExit()
    {
        onMouseExit();
    }
    void MouseStay()
    {
        onMouseStay();
    }
    bool AABBDetect(Vec2 point)
    {
        point += Vec2(width / 2, height / 2);
        if (point.x > x && point.x < x + width && point.y > y && point.y < y + height)
        {
            return true;
        }
        return false;
    }
    void Actions(Vec2 point)
    {
        bool result = AABBDetect(point);
        if (result)
        {
            if (isMouseEnter)
            {
                MouseStay();
            }
            else
            {
                isMouseEnter = true;
                MouseEnter();
            }
        }
        else
        {
            if (isMouseEnter)
            {
                isMouseEnter = false;
                MouseExit();
            }
        }
    }
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
    SeewkObject &SetMouseEnter(std::function<void()> f)
    {
        onMouseEnter = f;
        return *this;
    }
    SeewkObject &SetMouseExit(std::function<void()> f)
    {
        onMouseExit = f;
        return *this;
    }
    SeewkObject &SetMouseStay(std::function<void()> f)
    {
        onMouseStay = f;
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