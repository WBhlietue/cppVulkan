#include <core/vulkan/window.hpp>

seewk::core::vulkan::Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window_ = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window_, this);
}
seewk::core::vulkan::Window::~Window()
{
}
GLFWwindow *seewk::core::vulkan::Window::getWindow()
{
    return window_;
}
glm::vec2 seewk::core::vulkan::Window::getWindowSize()
{
    int width, height;
    glfwGetWindowSize(window_, &width, &height);
    return glm::vec2(width, height);
}
void seewk::core::vulkan::Window::setWindowSize(glm::vec2 size)
{
    glfwSetWindowSize(window_, size.x, size.y);
}
void seewk::core::vulkan::Window::setWindowTitle(std::string title)
{
    glfwSetWindowTitle(window_, title.c_str());
}
std::string seewk::core::vulkan::Window::getWindowTitle()
{
    const char *title = glfwGetWindowTitle(window_);
    return std::string(title);
}
void seewk::core::vulkan::Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(window_, callback);
}
void seewk::core::vulkan::Window::setMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(window_, callback);
}

void seewk::core::vulkan::Window::setPosition(glm::vec2 position)
{
    glfwSetWindowPos(window_, position.x, position.y);
}
glm::vec2 seewk::core::vulkan::Window::getPosition()
{
    int x, y;
    glfwGetWindowPos(window_, &x, &y);
    return glm::vec2(x, y);
}