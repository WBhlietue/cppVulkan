#include <core/vulkan/surface.hpp>
#include <core/vulkan/log.hpp>
#include <glfw/glfw3.h>
using namespace seewk::core::vulkan;

void Surface::Init(const Window &window)
{
    Log::print("Creating surface... new");
    VkSurfaceKHR surf;
    VkResult result = glfwCreateWindowSurface(Instance::GET().getInstance(), window.getWindow(), nullptr, &surf);
    if (result != VK_SUCCESS)
    {
    }
    else
    {
        surface = surf;
    }
    Log::print("Surface created. new");
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