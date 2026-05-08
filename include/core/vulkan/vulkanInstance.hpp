#pragma once

#include <vulkan/vulkan.hpp>

namespace seewk::core::vulkan{
class VulkanInstance {
    public:
        VulkanInstance();
        vk::Instance getInstance();
    private:
        vk::Instance instance;
        void Init();
};
}