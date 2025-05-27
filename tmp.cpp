#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>

int main2()
{
    std::ifstream file("./UI/main.json"); 
    if (!file.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return -1;
    }
    nlohmann::json j;
    file >> j; 

    // 访问数据
    for (auto& el : j.items()) {
        std::cout << "key: " << el.key() << ", value: " << el.value() << std::endl;
    }

    return 0;
}