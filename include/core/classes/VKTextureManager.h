#ifndef VKTextureManager_h
#define VKTextureManager_h

#include<vulkan/vulkan.h>
#include<string>
#include<vector>
#include<stb_image.h>

#define STB_IMAGE_IMPLEMENTATION

struct Texture
{
    VkImage image;
    VkDeviceMemory memory;
    VkImageView view;
    VkSampler sampler;
    uint32_t width, height;
};

class VKTextureManager
{
    public:
    std::vector<Texture> textures;
    void Init(VkDevice d, VkPhysicalDevice pd, VkCommandPool c, VkQueue q)
    {
        device = d;
        physicalDevice = pd;
        commandPool = c;
        graphicsQueue = q;
    }
    void LoadTexture(const std::string &path);

private:
    VkDevice device;
    VkPhysicalDevice physicalDevice;
    VkCommandPool commandPool;
    VkQueue graphicsQueue;


    void createImage(uint32_t width, uint32_t height, VkFormat format,
                     VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                     VkImage &image, VkDeviceMemory &imageMemory);

    VkImageView createImageView(VkImage image, VkFormat format);

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                      VkBuffer &buffer, VkDeviceMemory &bufferMemory);
};

#endif