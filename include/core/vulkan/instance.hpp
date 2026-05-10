#pragma once

#include <vulkan/vulkan.hpp>

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