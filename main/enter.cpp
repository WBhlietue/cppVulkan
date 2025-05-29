#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <optional>
#include <algorithm>
#include <fstream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

static std::vector<char> readFile(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "file read error -> " << fileName << std::endl;
    }
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

class HelloTriangleApplication
{
public:
    void Run()
    {
        InitWindow();
        int initResult = InitVulkan();
        if (initResult == 0)
        {
            if (CreateSurface())
            {
                std::cout << "surface created" << std::endl;
            }
            else
            {
                std::cout << "surface failed" << std::endl;
            }
            if (CreateSwapChain())
            {
                std::cout << "swapchain created" << std::endl;
            }
            else
            {
                std::cout << "swapchain failed" << std::endl;
            }
            CreateImageViews();
            CreateGraphicPipeline();
            MainLoop();
            Cleanup();
        }
        else if (initResult == 1)
        {
            std::cout << "vulkan init failed" << std::endl;
        }
        else if (initResult == 1)
        {
            std::cout << "no physical device found" << std::endl;
        }
    }

private:
    GLFWwindow *window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice vkDevice;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;

    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageView;
    VkFormat swapChainFormat;
    VkExtent2D swapChainExtent;

    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        bool isComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    struct SwapSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    void InitWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void CreateGraphicPipeline()
    {
        auto vertShader = readFile("./shader/test_vert.spv");
        auto fragShader = readFile("./shader/test_frag.spv");
    }

    bool CheckDevice(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProp;
        vkGetPhysicalDeviceProperties(device, &deviceProp);
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        std::cout << "\t" << "Device name: " << deviceProp.deviceName << std::endl;

        // 检查该显卡是否为独立显卡，独立显卡优先的话性能会比较好
        return deviceProp.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    }

    QueueFamilyIndices FindFamilys()
    {
        // 获得该显卡下支持的所有的列族，也就是指令的队列
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        QueueFamilyIndices indices;
        for (int i = 0; i < queueFamilies.size(); i++)
        {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }
            indices.presentFamily = i;
            if (indices.isComplete())
            {
                break;
            }
        }
        return indices;
    }

    int InitVulkan()
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "HI";
        appInfo.pEngineName = "HI_2";

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // 为了windows平台添加的窗口?

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // 验证层
        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
        {
            std::cout << result << std::endl;
            return 1;
        }

        // 扩展查看
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "Available extensions:" << std::endl;
        for (const auto &exten : extensions)
        {
            std::cout << "\t" << exten.extensionName << std::endl;
        }

        // 选择显卡
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0)
        {
            return 2;
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        std::cout << "All Devices" << std::endl;
        bool isSelected = false;
        for (const auto &device : devices)
        {
            if (CheckDevice(device))
            {
                physicalDevice = device;
                isSelected = true;
            }
        }
        if (!isSelected)
        {
            physicalDevice = devices[0];
        }

        VkPhysicalDeviceProperties deviceProp;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProp);
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
        std::cout << "Selected device name: " << deviceProp.deviceName << std::endl;

        QueueFamilyIndices indices = FindFamilys();
        if (!indices.isComplete())
        {
            return 3;
        }

        // 创建逻辑设备
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;

        // 优先级
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

        result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &vkDevice);
        if (result != VK_SUCCESS)
        {
            return 4;
        }

        // 查看列队
        VkQueue graphicsQueue;
        vkGetDeviceQueue(vkDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);

        return 0;
    }
    bool CheckDeviceExtension()
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensions.data());

        std::set<std::string> required(deviceExtensions.begin(), deviceExtensions.end());
        std::cout << "Device extensions:" << std::endl;
        for (const auto &ext : extensions)
        {
            std::cout << "\t" << ext.extensionName << std::endl;
            required.erase(ext.extensionName);
        }
        return required.empty();
    }

    SwapSupportDetails GetSupport()
    {
        SwapSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

        if (formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
        }
        return details;
    }

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormat)
    {
        for (const auto &formats : availableFormat)
        {
            if (formats.format == VK_FORMAT_B8G8R8A8_SRGB && formats.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return formats;
            }
        }
        return availableFormat[0];
    }
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
    {
        for (const auto &presentMode : availablePresentModes)
        {
            if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return presentMode;
            }
            return VK_PRESENT_MODE_FIFO_KHR;
        }
    }

    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capability)
    {
        if (capability.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return capability.currentExtent;
        }
        else
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actual = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)};

            actual.width = std::clamp(actual.width, capability.minImageExtent.width, capability.maxImageExtent.width);
            actual.height = std::clamp(actual.height, capability.minImageExtent.height, capability.maxImageExtent.height);

            return actual;
        }
    }

    bool CreateSwapChain()
    {
        SwapSupportDetails support = GetSupport();
        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(support.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(support.presentModes);
        VkExtent2D extent = ChooseSwapExtent(support.capabilities);

        uint32_t imageCount = support.capabilities.minImageCount + 1;
        if (support.capabilities.maxImageCount > 0 && imageCount > support.capabilities.maxImageCount)
        {
            imageCount = support.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;                             // 2d 中为1，3d的是别的
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // 直接用它的颜色
        createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;     // 需要后处理

        QueueFamilyIndices indices = FindFamilys();
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = support.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult result = vkCreateSwapchainKHR(vkDevice, &createInfo, nullptr, &swapChain);
        if (result != VK_SUCCESS)
        {
            return false;
        }

        vkGetSwapchainImagesKHR(vkDevice, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(vkDevice, swapChain, &imageCount, swapChainImages.data());

        swapChainFormat = surfaceFormat.format;
        swapChainExtent = extent;

        return true;
    }

    void CreateImageViews()
    {
        swapChainImageView.resize(swapChainImages.size());
        for (int i = 0; i < swapChainImages.size(); i++)
        {

            VkImageViewCreateInfo createinfo{};
            createinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createinfo.image = swapChainImages[i];

            createinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createinfo.format = swapChainFormat;
            createinfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createinfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createinfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createinfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

            createinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createinfo.subresourceRange.baseMipLevel = 0;
            createinfo.subresourceRange.levelCount = 1;
            createinfo.subresourceRange.baseArrayLayer = 0;
            createinfo.subresourceRange.layerCount = 1;

            VkResult result = vkCreateImageView(vkDevice, &createinfo, nullptr, &swapChainImageView[i]);
            if (result != VK_SUCCESS)
            {
                std::cout << "failed to create image view" << std::endl;
            }
        }
    }

    bool CreateSurface()
    {
        VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
        if (result != VK_SUCCESS)
        {
            return false;
        }

        return true;
    }

    void MainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void Cleanup()
    {

        for (auto v : swapChainImageView)
        {
            vkDestroyImageView(vkDevice, v, nullptr);
        }
        vkDestroySwapchainKHR(vkDevice, swapChain, nullptr);
        vkDeviceWaitIdle(vkDevice);

        vkDestroyDevice(vkDevice, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);
        glfwTerminate();
    };
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}