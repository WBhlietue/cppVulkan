// #include<core/vulkan/vulkanCore.hpp>
#include<core/vulkan/log.hpp>
#include<enter.h>
import VulkanCore;
import Main;
// import seewk.VulkanCore;

int main()
{
    seewk::core::vulkan::Log::print("program start");
    try
    {
        VulkanCore &app = getCore();
        seewk::core::vulkan::Log::print("program run");
        OnStart();
        app.run();
        OnOver();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
int VKLoadTexture(std::string imagePath)
{
    VulkanCore &app = getCore();
    return 0;
    // return app.win.LoadTexture(imagePath);
}
void AddShape(Object object)
{
    VulkanCore &app = getCore();
    // app.win.AddObject(object);
}