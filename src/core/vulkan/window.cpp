#include <core/vulkan/window.hpp>

using namespace seewk::core::vulkan;

Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window_ = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window_, this);
}
Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}
GLFWwindow *Window::getWindow() const
{
    return window_;
}
glm::vec2 Window::getWindowSize()
{
    int width, height;
    glfwGetWindowSize(window_, &width, &height);
    return glm::vec2(width, height);
}
void Window::setWindowSize(glm::vec2 size)
{
    glfwSetWindowSize(window_, size.x, size.y);
}
void Window::setWindowTitle(std::string title)
{
    glfwSetWindowTitle(window_, title.c_str());
}
std::string Window::getWindowTitle()
{
    const char *title = glfwGetWindowTitle(window_);
    return std::string(title);
}
void Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(window_, callback);
}
void Window::setMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(window_, callback);
}

void Window::setPosition(glm::vec2 position)
{
    glfwSetWindowPos(window_, position.x, position.y);
}
glm::vec2 Window::getPosition()
{
    int x, y;
    glfwGetWindowPos(window_, &x, &y);
    return glm::vec2(x, y);
}