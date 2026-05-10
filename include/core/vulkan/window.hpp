#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
namespace seewk::core::vulkan
{
    class Window
    {
    public:
        Window();
        ~Window();
        GLFWwindow *getWindow() const;
        glm::vec2 getWindowSize();
        void setWindowSize(glm::vec2 size);
        void setWindowTitle(std::string title);
        std::string getWindowTitle();
        void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
        void setMouseButtonCallback(GLFWmousebuttonfun callback);
        void setPosition(glm::vec2 position);
        glm::vec2 getPosition();

    private:
        GLFWwindow *window_;
    };
}