#pragma once

#include <vulkan/vulkan.hpp>

namespace seewk::core::vulkan{
class VulkanInstance {
    public:
        VulkanInstance();
        ~VulkanInstance();
        vk::Instance getInstance();
    private:
        vk::Instance instance_;
};
}