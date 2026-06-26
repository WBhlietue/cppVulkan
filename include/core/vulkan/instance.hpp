#pragma once

#include <vulkan/vulkan.hpp>
// import vulkanBase;

namespace seewk::core::vulkan
{
    class Instance
    {
    public:
        ~Instance();
        static seewk::core::vulkan::Instance &GET();
        vk::Instance &getInstance();

    private:
        vk::Instance instance;
        Instance();
    };
}