#include <main.h>
#include <iostream>
#include <core/core.h>
#include <cmath>

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

void LoadTextures(){
    texture = Load_Texture("assets/test.jpg");
    std::cout << texture << std::endl;
}

void OnStart()
{
    obj3 = DrawRectangle(100, 100, 100, 200, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 50);
    obj = DrawRectangle(400, 200, 300, -100, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 30);
    obj2 = DrawRectangle(100, 100, 0, 0, glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), 10);
    MoveShape(obj, 100, -40);
    AddOnClick(obj, []()
               {
                if(obj.texture_id == 0){
                    obj.SetTexture(-1);
                }else{
                    obj.SetTexture(0);
               }
                if(!isMoving){
                        isMoving = true;
                    } });
    AddOnClick(obj2, []()
               { shape2Move = !shape2Move; });

    AddOnClick(obj3, []()
               {
        b = -1;
        forward = true; });
    obj.SetTexture(texture);
}

void OnUpdate(float deltaTime)
{
    std::cout << "frame rate: " << 1 / deltaTime << std::endl;

    if (isMoving)
    {
        if (isTestForward)
        {
            test += deltaTime * 2;
            if (test >= 1)
            {
                isMoving = false;
                isTestForward = false;
            }
        }
        else
        {
            test -= deltaTime * 2;
            if (test <= 0)
            {
                isMoving = false;
                isTestForward = true;
            }
        }
        MoveShape(obj, 100, -40 + 200 * test * test);
    }
    if (shape2Move)
    {
        a += deltaTime*0.5;
        if (a >= 1)
        {
            a -= 1;
        }
        MoveShape(obj2, centerX + radius * cos(a * 2 * PI), centerY + radius * sin(a * 2 * PI));
    }
    if (forward)
    {
        b += deltaTime * 2;
        if (b >= 1)
        {
            forward = false;
        }
    }
    else
    {
        b -= deltaTime * 2;
        if (b <= -1)
        {
            forward = true;
        }
    }

    MoveShape(obj3, 300 * b, -200);
}