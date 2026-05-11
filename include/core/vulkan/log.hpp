#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
namespace seewk::core::vulkan
{
    class Log
    {
    public:
        template <typename... Args>
        static void print(Args &&...args)
        {
            auto now = std::chrono::system_clock::now();
            auto now_time_t = std::chrono::system_clock::to_time_t(now);
            auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                              now.time_since_epoch()) %
                          1000;

            std::tm now_tm;
            localtime_s(&now_tm, &now_time_t);
            std::cout << "["
                      << std::setfill('0') << std::setw(2) << now_tm.tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << now_tm.tm_min << ":"
                      << std::setfill('0') << std::setw(2) << now_tm.tm_sec << "."
                      << std::setfill('0') << std::setw(3) << now_ms.count()
                      << "] ";

            ((std::cout << std::forward<Args>(args)), ...);
            std::cout << std::endl;
        }
    };
}