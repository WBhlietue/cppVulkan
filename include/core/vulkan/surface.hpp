#pragma once

#include <vulkan/vulkan.hpp>
#include <core/vulkan/instance.hpp>
#include <core/vulkan/window.hpp>
namespace seewk::core::vulkan
{
    class Surface
    {
    public:
        
        void Init(const seewk::core::vulkan::Window &window);
        ~Surface();
        const vk::SurfaceKHR &getSurface() const;

    private:
        vk::SurfaceKHR surface;
    };
};