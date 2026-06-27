

#include <glfw/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <core/vulkan/instance.hpp>
#include <core/vulkan/log.hpp>
#include <vector>

using namespace seewk::core::vulkan;
// std::vector<const char*> getRequiredExtensions() {
//     std::vector<const char*> extensions;
//     extensions.push_back("VK_KHR_surrface");
//     extensions.push_back("VK_KHR_win32_surface");
    
//     // 如果你启用了验证层或调试工具，再加：
//     // extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    
//     return extensions;
// }

std::vector<const char *> getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    // for(int i = 0; i < glfwExtensionCount; i++)
    // {
    //     std::cout << glfwExtensions[i] << std::endl;
    // }
    return extensions;
}

Instance::Instance()
{
    Log::print("Creating vulkan instance...");
    vk::ApplicationInfo appInfo{};
    Log::print("start");
    appInfo.setPApplicationName("vulkanApp")
        .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
        .setPEngineName("No Engine")
        .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
        .setApiVersion(VK_API_VERSION_1_0);
        Log::print("done");
    auto extensions = getRequiredExtensions();
    Log::print("a");
    vk::InstanceCreateInfo createInfo(
        {},
        &appInfo,
        0,
        nullptr,
        static_cast<uint32_t>(extensions.size()),
        extensions.data());
        Log::print("aaa");
    try
    {
        instance = vk::createInstance(createInfo);
    }
    catch (const vk::SystemError &e)
    {
        throw std::runtime_error(e.what());
    }
    Log::print("Instance created successfully.");
}

Instance &Instance::GET()
{
    static Instance ins;
    return ins;
}
vk::Instance &Instance::getInstance()
{
    return instance;
}

Instance::~Instance()
{
    if (instance)
    {
        instance.destroy();
    }
}
