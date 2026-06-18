#pragma once
#include <glm/glm.hpp>
#include <enter.h>
#include <functional>
#include <enter.h>
#include <vector>
#include <core/vulkan/appWindow.hpp>
#include<core/main/windowManager.hpp>

#include<core/main/seewkObject.hpp>
#include<core/interface/iwindow.hpp>
namespace seewk::main
{
    static int objectID = 0;
    enum FormType
    {
        NO_UPDATE,
        USE_UPDATE
    };
    class Form: public AppWindow
    {
    public:
        FormType type = FormType::USE_UPDATE;



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
            AppWindow::AddObject(object);
            return object;
        }
        void Close(){
            // delete this;
        }

        SwkObject CreateObject(){
            return IWindow::CreateSeewkObject();
        }


    private:
        std::vector<int> objects;
        // AppWindow wind ;
    protected:
        virtual void OnShow() {}
    };
}