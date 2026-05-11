#include <core/vulkan/surface.hpp>
#include <core/vulkan/log.hpp>
#include <glfw/glfw3.h>
using namespace seewk::core::vulkan;
Surface::Surface(const Window &window)
{
    Log::print("Creating surface...");
    VkSurfaceKHR surf;
    VkResult result = glfwCreateWindowSurface(Instance::GET().getInstance(), window.getWindow(), nullptr, &surf);
    if (result != VK_SUCCESS)
    {
    }
    else
    {
        surface = surf;
    }
    Log::print("Surface created.");
}
const vk::SurfaceKHR &Surface::getSurface() const
{
    return surface;
}
Surface::~Surface()
{
    if (surface)
    {
        Instance::GET().getInstance().destroySurfaceKHR(surface, nullptr);
    }
}