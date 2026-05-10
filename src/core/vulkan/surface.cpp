#include <core/vulkan/surface.hpp>
#include <glfw/glfw3.h>
using namespace seewk::core::vulkan;
Surface::Surface(const Window &window)
{
    VkSurfaceKHR surf;
    VkResult result = glfwCreateWindowSurface(Instance::GET().getInstance(), window.getWindow(), nullptr, &surf);
    if (result != VK_SUCCESS)
    {
    }
    else
    {
        surface = surf;
    }
}
const vk::SurfaceKHR &Surface::getSurface() const
{
    return surface;
}
Surface::~Surface()
{
    if (surface)
    {
        vkDestroySurfaceKHR(Instance::GET().getInstance(), surface, nullptr);
    }
}