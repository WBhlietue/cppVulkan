// #pragma once
// #include <glm/glm.hpp>
// #include <enter.h>
// #include <functional>
// #include <main/object.hpp>
// #include <vector>
// #include <core/vulkan/appWindow.hpp>

// namespace seewk::main
// {
//     enum FormType
//     {
//         NO_UPDATE,
//         USE_UPDATE
//     };
//     class Form : seewk::core::vulkan::AppWindow
//     {
//     public:
//         FormType type = FormType::USE_UPDATE;
//         Form():AppWindow()
//         {

//         }


//         void Show()
//         {
//         }

//     private:
//         std::vector<seewk::main::Object> objects;

//     protected:
//         virtual void OnLoad() {}
//         virtual void OnUpdate() {}
//         seewk::main::Object &GetObject()
//         {
//             return objects.emplace_back();
//         }
//     };
// }