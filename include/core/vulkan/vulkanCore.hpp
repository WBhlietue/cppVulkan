#pragma once

#include <core/vulkan/appWindow.hpp>

class VulkanCore
{
public:
    // AppWindow win;
    void run()
    {
        windows[0]->Loop();
        // auto lastTime = std::chrono::high_resolution_clock::now();
        // const float targetFrameTime = 1.0f / 60.0f;
        // while (!glfwWindowShouldClose(windows[0]->window.getWindow()))
        // {
            
        //     auto currentTime = std::chrono::high_resolution_clock::now();
            
        //     std::chrono::duration<float> deltaTime = currentTime - lastTime;
            
        //     lastTime = currentTime;
            
            
        //     for (int i = 0; i < windows.size(); i++)
        //     {
        //         windows[i]->Loop();
        //     }
        // }

        // vkDeviceWaitIdle(device);
    };
    // void AddWindow(AppWindow &window)
    // {
    //     windows.push_back(window);
    // }

private:
    WindowManager &manager = GetWindowManager();
    std::vector<AppWindow *> &windows = manager.GetWindows();

    //     std::vector<AppWindow> windows;
};

VulkanCore &getCore()
{
    static VulkanCore app;
    return app;
}