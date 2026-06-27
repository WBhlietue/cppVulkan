#pragma once
#include <core/types.hpp>
#include <core/classes/vkObject.h>
#include <functional>

// using S_Object = SeewkObject&;
constexpr int MOUSE_ENTER = 0;
constexpr int MOUSE_STAY = 1;
constexpr int MOUSE_EXIT = 2;
constexpr int MOUSE_DOWN = 3;
constexpr int MOUSE_DRAG = 4;
constexpr int MOUSE_UP = 5;
constexpr int MOUSE_CLICK = 6;
constexpr int MOUSE_NONE = 7;
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
    std::function<void(int)> onMouseDown = [](int button) {};
    std::function<void(int)> onMouseUp = [](int button) {};
    std::function<void(int)> onMouseClick = [](int button) {};
    std::function<void(int)> onMouseDrag = [](int button) {};
    bool isMouseEnter = false;
    int mouseDownX;
    int mouseDownY;
    int clickThreshold = 10;

public:
    SeewkObject() {}
    ~SeewkObject() {}
    bool MouseEnter()
    {
        isMouseEnter = true;
        if (onMouseEnter)
        {
            onMouseEnter();
            return true;
        }
        return false;
    }
    bool MouseExit()
    {
        isMouseEnter = false;
        if (onMouseExit)
        {
            onMouseExit();
            return true;
        }
        return false;
    }
    bool MouseStay()
    {
        if (onMouseStay)
        {
            onMouseStay();
            return true;
        }
        return false;
    }
    bool MouseDown(int button, int mX, int mY)
    {
        if (onMouseDown)
        {
            onMouseDown(button);
            mouseDownX = mX;
            mouseDownY = mY;
            return true;
        }
        return false;
    }
    bool MouseUp(int button, int mX, int mY)
    {
        if (abs(mouseDownX - mX) < clickThreshold && abs(mouseDownY - mY) < clickThreshold)
        {
            return MouseClick(button);
        }
        if (onMouseUp)
        {
            onMouseUp(button);
            return true;
        }
        return false;
    }
    bool MouseClick(int button)
    {
        if (onMouseClick)
        {
            onMouseClick(button);
            return true;
        }
        return false;
    }
    bool MouseDrag(int button)
    {
        if (onMouseDrag)
        {
            onMouseDrag(button);
            return true;
        }
        return false;
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
    int Actions(Vec2 point)
    {
        bool result = AABBDetect(point);
        if (result)
        {
            if (isMouseEnter)
            {
                if (MouseStay())
                    return MOUSE_STAY;
            }
            else
            {

                if (MouseEnter())
                    return MOUSE_ENTER;
            }
        }
        else
        {
            if (isMouseEnter)
            {
                if (MouseExit())
                    return MOUSE_EXIT;
            }
        }
        return MOUSE_NONE;
    }
    int ActionsButton(Vec2 point, int button, int action, int mods)
    {
        if (AABBDetect(point))
        {
            if (action == GLFW_PRESS)
            {
                if (MouseDown(button, point.x, point.y))
                    return MOUSE_DOWN;
            }
            else if (action == GLFW_RELEASE)
            {
                if (MouseUp(button, point.x, point.y))
                    return MOUSE_UP;
            }
        }
        return MOUSE_NONE;
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
    SeewkObject &SetMouseUp(std::function<void(int)> f)
    {
        onMouseUp = f;
        return *this;
    }
    SeewkObject &SetMouseDown(std::function<void(int)> f)
    {
        onMouseDown = f;
        return *this;
    }
    SeewkObject &SetClick(std::function<void(int)> f)
    {
        onMouseClick = f;
        return *this;
    }
    SeewkObject &SetDrag(std::function<void(int)> f)
    {
        onMouseDrag = f;
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