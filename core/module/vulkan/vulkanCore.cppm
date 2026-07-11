module;
export module VulkanCore;
import AppWindow;
import WindowManager;
import seewk.tween;
export class VulkanCore
{

public:
    TweenManager& tManager;
    VulkanCore():tManager(TweenManager::GetInstance())
    {
       
    }
    void run()
    {
        auto lastTime = std::chrono::high_resolution_clock::now();
        const float targetFrameTime = 1.0f / 60.0f;
        while (seewk::WindowManager::IsWindow())
        {

            auto currentTime = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float> deltaTime = currentTime - lastTime;

            lastTime = currentTime;
            tManager.Loop(deltaTime.count());
            seewk::WindowManager::Loop(deltaTime.count());
        }
    };
};

export VulkanCore &getCore()
{
    static VulkanCore app;
    return app;
}