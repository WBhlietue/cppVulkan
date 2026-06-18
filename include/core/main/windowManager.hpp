#pragma once
#include <core/interface/iwindow.hpp>
#include <vector>
#include <memory>
#include <concepts>
#include <core/vulkan/window.hpp>

namespace seewk
{
    class WindowManager
    {
        static inline std::vector<std::unique_ptr<IWindow>> windows={};

    public:
        template <std::derived_from<IWindow> T>
            requires std::is_default_constructible_v<T>
        static T &CreateWindow()
        {
            std::unique_ptr<T> ptr = std::make_unique<T>();
            auto p = ptr.get();
            windows.push_back(std::move(ptr));
            p->OnLoad();
            return *p;
        }
        
        static void Loop(float deltaTime)
        {
            for (int i = 0; i < windows.size(); i++)
            {
                windows[i]->Loop();
                windows[i]->OnLoop(deltaTime);
            }
        }
        static bool IsWindow(){
            if(windows.size() > 0){
                return windows[0]->isWindow();
            }
            return false;
        }
    };
}