#include <core/vulkan/device.hpp>
#include <core/vulkan/instance.hpp>
#include <optional>
#include <set>
#include <iostream>
#include <core/vulkan/log.hpp>

using namespace seewk::core::vulkan;

std::vector<char *> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};
struct SwapChainSupportDetails
{
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

bool checkDeviceExtensionSupport(vk::PhysicalDevice device)
{
    auto extensions = device.enumerateDeviceExtensionProperties();

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (auto &extension : extensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface)
{
    QueueFamilyIndices indices;

    auto queueFamilies = device.getQueueFamilyProperties();

    int i = 0;
    for (auto &queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
        {
            indices.graphicsFamily = i;
        }

        if (device.getSurfaceSupportKHR(i, surface))
        {
            indices.presentFamily = i;
        }

        if (indices.isComplete())
            break;
        i++;
    }

    return indices;
}
SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice device, vk::SurfaceKHR surface)
{
    SwapChainSupportDetails details;

    details.capabilities = device.getSurfaceCapabilitiesKHR(surface);
    details.formats = device.getSurfaceFormatsKHR(surface);
    details.presentModes = device.getSurfacePresentModesKHR(surface);

    return details;
}

bool isDeviceSuitable(vk::PhysicalDevice device, vk::SurfaceKHR surface)
{
    auto indices = findQueueFamilies(device, surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        auto swapChainSupport = querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

void Device::pickPhysicalDevice(Surface &surface)
{

    std::vector<vk::PhysicalDevice> devices = Instance::GET().getInstance().enumeratePhysicalDevices();
    if (devices.size() == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    bool isAdd = false;
    // vk::PhysicalDevice physicalDevice = VK_NULL_HANDLE;
    for (auto &device : devices)
    {

        vk::PhysicalDeviceProperties deviceProperties = device.getProperties();
        if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && isDeviceSuitable(device, surface.getSurface()))
        {
            Log::print(deviceProperties.deviceName);
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
    // return physicalDevice;
}

void Device::createLogicalDevice(Surface &surface)
{
    Log::print("start create logical device");
    auto indices = findQueueFamilies(physicalDevice, surface.getSurface());

    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        vk::DeviceQueueCreateInfo queueCreateInfo;
        queueCreateInfo.setFlags({})
            .setQueueFamilyIndex(queueFamily)
            .setQueueCount(1)
            .setPQueuePriorities(&queuePriority);
        queueCreateInfos.push_back(queueCreateInfo);
    }

    vk::PhysicalDeviceFeatures deviceFeatures;

    vk::PhysicalDeviceDescriptorIndexingFeaturesEXT indexingFeatures;
    indexingFeatures.setShaderSampledImageArrayNonUniformIndexing(true)
        .setRuntimeDescriptorArray(true)
        .setDescriptorBindingVariableDescriptorCount(true)
        .setDescriptorBindingPartiallyBound(true);

    vk::DeviceCreateInfo createInfo;
    createInfo.setFlags({})
        .setQueueCreateInfos(queueCreateInfos)
        .setEnabledExtensionCount(static_cast<uint32_t>(deviceExtensions.size()))
        .setPpEnabledExtensionNames(deviceExtensions.data())
        .setPEnabledFeatures(&deviceFeatures)
        .setPNext(&indexingFeatures);

    device = physicalDevice.createDevice(createInfo);

    graphicsQueue = device.getQueue(indices.graphicsFamily.value(), 0);
    presentQueue = device.getQueue(indices.presentFamily.value(), 0);
    Log::print("end create logical device ", device);
}

void Device::init(Surface &surface)
{
    // Window w;

    // Surface surf(window);
    Log::print(surface.getSurface());
    pickPhysicalDevice(surface);
    createLogicalDevice(surface);
    Log::print("init device success");
}
Device::Device()
{
}
vk::Device Device::getDevice()
{
    return device;
}
vk::PhysicalDevice Device::getPhysicalDevice()
{
    return physicalDevice;
}
vk::Queue Device::getGraphicsQueue()
{
    return graphicsQueue;
}
vk::Queue Device::getPresentQueue()
{
    return presentQueue;
}
Device::~Device()
{
    device.destroy();
}
