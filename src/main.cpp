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

float centerX = -100;
float centerY = 200;
float radius = 100;

void OnStart()
{
    obj = DrawRectangle(200, 100, 0, 0, glm::vec3(1.0f, 0.0f, 1.0f));
    obj2 = DrawRectangle(100, 100, -100, -100, glm::vec3(0.0f, 0.0f, 1.0f));
    obj3 = DrawRectangle(100, 100, 0, 0, glm::vec3(0.0f, 1.0f, 0.0f));
    MoveShape(obj, 100, 100);
}

void OnUpdate(float deltaTime)
{
    // std::cout << "frame rate: " << 1 / deltaTime << std::endl;

    a += deltaTime;
    if (a >= 1)
    {
        a -= 1;
    }
    if (forward)
    {
        b += deltaTime * 3;
        if (b >= 1)
        {
            forward = false;
        }
    }
    else
    {
        b -= deltaTime * 3;
        if (b <= -1)
        {
            forward = true;
        }
    }
    MoveShape(obj2, centerX + radius * cos(a * 2 * PI), centerY + radius * sin(a * 2 * PI));
    MoveShape(obj3, 300 * b, -200);
    // MoveShape(obj, 100, -100 + a * 200);
}