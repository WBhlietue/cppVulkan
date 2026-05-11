#pragma once

#include <vulkan/vulkan.hpp>
#include <core/vulkan/surface.hpp>
namespace seewk::core::vulkan
{
    
    class Device
    {
    public:
        Device();
        ~Device();
        void init(Surface &surface);
        vk::Device getDevice();
        vk::PhysicalDevice getPhysicalDevice();
        vk::Queue getGraphicsQueue();
        vk::Queue getPresentQueue();

    private:
        vk::PhysicalDevice physicalDevice;
        vk::Device device;
        vk::Queue graphicsQueue;
        vk::Queue presentQueue;
        void pickPhysicalDevice(Surface &surface);
        void createLogicalDevice(Surface &surface);
    };
}