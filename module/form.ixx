module;
#include <glm/glm.hpp>
#include <enter.h>
#include <functional>
#include <enter.h>
#include <vector>

#include <core/main/seewkObject.hpp>
#include <core/interface/iwindow.hpp>
export module Form;
import AppWindow;
import WindowManager;
namespace seewk::main
{
    static int objectID = 0;
    enum FormType
    {
        NO_UPDATE,
        USE_UPDATE
    };
    export class Form : public IWindow
    {
        AppWindow appWindow;

    public:
        Form() : appWindow(this)
        {
        }
        void Loop() override
        {
            appWindow.Loop();
        }
        bool isWindow() override
        {
            return appWindow.isWindow();
        }
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
            appWindow.AddObject(object);
            return object;
        }
        void Close()
        {
            // delete this;
        }

        SwkObject CreateObject()
        {
            return IWindow::swkObjectCreate();
        }
        Vec2 GetMousePosition()
        {
            return appWindow.GetMousePosition();
        }


    private:
        std::vector<int> objects;
        // AppWindow wind ;
    protected:
        virtual void OnShow() {}
    };
}