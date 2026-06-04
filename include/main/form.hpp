#pragma once
#include <glm/glm.hpp>
#include <enter.h>
#include <functional>
#include <enter.h>
#include <vector>
#include <core/vulkan/appWindow.hpp>

namespace seewk::main
{
    static int objectID = 0;
    enum FormType
    {
        NO_UPDATE,
        USE_UPDATE
    };
    class Form
    {
    public:
        FormType type = FormType::USE_UPDATE;

        Form()
        {
            OnLoad();
        }

        void Show()
        {
            OnShow();
        }
        Object DrawRectangle(int width, int height, int x, int y, glm::vec4 color, float borderRadius)
        {
            Object object;
            object.id = objectID++;
            object.width = width;
            object.height = height;
            object.x = x;
            object.y = y;
            object.color = color;
            object.borderRadius = borderRadius;
            wind.AddObject(object);
            return object;
        }

    private:
        std::vector<int> objects;
        AppWindow wind;

    protected:
        virtual void OnLoad() {}
        virtual void OnShow() {}
        virtual void OnUpdate() {}
    };
}