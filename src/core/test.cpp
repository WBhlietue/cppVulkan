#include <vulkan/vulkan.hpp>
#include <core/vulkan/log.hpp>
int maink()
{
    seewk::core::vulkan::Log::print("test start");
    vk::ApplicationInfo appInfo;
    appInfo.setApiVersion(VK_API_VERSION_1_0);

    vk::InstanceCreateInfo createInfo;
    createInfo.setPApplicationInfo(&appInfo);
    createInfo.setEnabledLayerCount(0);
    seewk::core::vulkan::Log::print("create instance");
    auto instance = vk::createInstance(createInfo);
    seewk::core::vulkan::Log::print("end create instance");
    instance.destroy();

    return 0;
}