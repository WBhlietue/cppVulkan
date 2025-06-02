#include <main.h>
#include <iostream>
#include <core/core.h>

std::string mainPage = "main";
Object obj;

float a = 0;
bool forward = true;

void OnStart()
{
    obj = DrawRectangle(200, 100, 0, 0, glm::vec3(1.0f, 0.0f, 1.0f));
    MoveShape(obj, 100, 100);
}

void OnUpdate(float deltaTime)
{
    std::cout << "frame rate: " << 1 / deltaTime << std::endl;
    if (forward)
    {
        a += deltaTime;
        if (a >= 1)
        {
            forward = false;
        }
    }
    else
    {
        a -= deltaTime;
        if (a <= 0)
        {
            forward = true;
        }
    }
    MoveShape(obj, 0, -100 + a * 200);
}