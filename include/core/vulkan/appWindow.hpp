#pragma once

#include <vulkan/vulkan.hpp>
#include<core/vulkan/window.hpp>
#include<core/vulkan/surface.hpp>
#include<string>
namespace seewk::core::vulkan
{
    class AppWindow
    {
        public:
            AppWindow(std::string title, int width, int height);
            ~AppWindow();
        private:
            Window window;
            Surface surface;
    };

}