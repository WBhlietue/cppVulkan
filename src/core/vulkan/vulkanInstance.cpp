

#include <glfw/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <core/vulkan/vulkanInstance.hpp>
#include <vector>

std::vector<const char *> getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    return extensions;
}

seewk::core::vulkan::VulkanInstance::VulkanInstance()
{
    vk::ApplicationInfo appInfo{};
    appInfo.setPApplicationName("vulkanApp")
        .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
        .setPEngineName("No Engine")
        .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
        .setApiVersion(VK_API_VERSION_1_0);
    auto extensions = getRequiredExtensions();
    vk::InstanceCreateInfo createInfo(
        {},
        &appInfo,
        0,
        nullptr,
        static_cast<uint32_t>(extensions.size()),
        extensions.data());
    try
    {
        instance_ = vk::createInstance(createInfo);
    }
    catch (const vk::SystemError &e)
    {
        throw std::runtime_error(e.what());
    }
}

vk::Instance seewk::core::vulkan::VulkanInstance::getInstance()
{
    return instance_;
}

seewk::core::vulkan::VulkanInstance::~VulkanInstance()
{
    if (instance_)
    {
        // instance.destroy();
    }
}
