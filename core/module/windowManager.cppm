module;
#include <core/interface/iwindow.hpp>
#include <vector>
#include <memory>
#include <future>
#include <concepts>
#include <core/vulkan/window.hpp>
#include <core/vulkan/log.hpp>
export module WindowManager;
using Log = seewk::core::vulkan::Log;
namespace seewk
{
    export class WindowManager
    {
        static inline std::vector<std::unique_ptr<IWindow>> windows = {};

    public:
        template <std::derived_from<IWindow> T>
            requires std::is_default_constructible_v<T>
        static T &CreateWindow()
        {
            std::unique_ptr<T> ptr = std::make_unique<T>();
            auto p = ptr.get();
            Log::print("create window-------------------------------");
            auto init_future = std::async(std::launch::async, [p]()
                                          { p->InitWindow(); });
            Log::print("create window done--------------------------");
            windows.push_back(std::move(ptr));
            std::cout << "im waiting" << std::endl;
            while (true)
            {
                auto status = init_future.wait_for(std::chrono::seconds(0));
                if (status == std::future_status::ready)
                {
                    break;
                }

                glfwPollEvents();
            }
            return *p;
        }

        static void Loop(float deltaTime)
        {
            for (int i = 0; i < windows.size(); i++)
            {
                windows[i]->Loop();
                windows[i]->OnLoop(deltaTime);
            }
        }
        static bool IsWindow()
        {
            if (windows.size() > 0)
            {
                return windows[0]->isWindow();
            }
            return false;
        }
    };
}