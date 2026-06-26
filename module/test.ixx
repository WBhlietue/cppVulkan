export module test;
#include <iostream>
#include <vulkan/vulkan.hpp>

export void RunTest()
{
    std::cout << "TESTING\n";
}

export void TEST()
{
    std::cout << "just testing\n";
}

export using vkInstance = vk::Instance;