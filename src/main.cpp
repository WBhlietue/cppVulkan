#include <main/form.hpp>
// #include <cmath>
// #include<main.h>
// #include<core/vulkan/log.hpp>

// class Form1: public seewk::main::Form{
//     seewk::main::Object obj1;
//     void OnLoad() override{
//         obj1 = GetObject();
//         obj1.SetPosition(glm::vec2(100, 100));
//         obj1.SetSize(glm::vec2(100, 100));
//     }
// };
// Form1 form;
// void LoadTextures(){

// }
// void OnStart(){
//     form.Show();
// }
// void OnUpdate(float deltaTime){

// }

#include <main.h>
#include <iostream>
#include <core/core.h>
#include <cmath>
#include <core/vulkan/log.hpp>

std::string mainPage = "main";
Object obj;
Object obj2;
Object obj3;

const float PI = 3.1415926;

float a = 0;
float b = 0;
bool forward = true;

float centerX = -200;
float centerY = 50;
float radius = 100;

bool isMoving = false;
bool isTestForward = true;
float test = 0;

bool shape2Move = true;

int texture;

void LoadTextures()
{
    texture = Load_Texture("assets/test.jpg");
}


class Form1 : public seewk::main::Form
{
public:
    // Form1()
    // {
    //     OnLoad();
    // }
    void OnLoad() 
    {

        obj = DrawRectangle(400, 200, 300, -100, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 30);
    }
};

class Form2 : public seewk::main::Form
{
public:
    // Form2()
    // {
    //     OnLoad();
    // }
    void OnLoad() 
    {
        obj = DrawRectangle(200, 100, 300, -100, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), 30);
    }
};

Form1 form;
Form2* form2;
void OnStart()
{
    form2 = new Form2();
}

void OnOver(){
    std::cout << "over\n";
    form2->Close();
}
void OnUpdate(float deltaTime)
{
}
