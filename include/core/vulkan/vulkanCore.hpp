#pragma once

#include<core/vulkan/appWindow.hpp>

class VulkanCore
{
    public:
    AppWindow win;
    void run(){
        win.run();
    };
};



VulkanCore &getCore()
{
    static VulkanCore app;
    return app;
}