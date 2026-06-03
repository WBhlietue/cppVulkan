#include<core/vulkan/vulkanCore.hpp>


int main()
{
    seewk::core::vulkan::Log::print("program start");
    try
    {
        VulkanCore &app = getCore();
        seewk::core::vulkan::Log::print("program run");
        app.run();
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
    return app.win.LoadTexture(imagePath);
}
void AddShape(Object object)
{
    VulkanCore &app = getCore();
    app.win.AddObject(object);
}