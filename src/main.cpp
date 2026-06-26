#include <seewk.hpp>
#include <cmath>
import test;
import vulkanBase;
const float PI = 3.1415926;


class Form1 : public seewk::main::Form
{
public:
    int angle = 0;
    int radius = 200;
    int speed = 10;
    int border = 30;
    int borderSpeed = 1;
    float r = 0, g = 0, b = 0;
    float speedR = 0.13f;
    float speedG = 0.17f;
    float speedB = 0.29f;
    SeewkObject *obj = nullptr;

    void OnLoad() override
    {

        obj = &CreateObject()
                   .SetPosition(Vec2(0, 0))
                   .SetSize(Vec2(100, 100))
                   .SetColor(Color(r, g, b, 1))
                   .SetBorderRadius(border);
    }
    void OnLoop(float deltaTime) override
    {
        angle += speed;
        int x = sin(angle * PI / 180.0) * radius;
        int y = cos(angle * PI / 180.0) * radius;
        obj->SetPosition(Vec2(x, y));
        border += borderSpeed;
        if (border < 10 || border > 50)
        {
            borderSpeed *= -1;
        }
        obj->SetBorderRadius(border);
        r += speedR;
        g += speedG;
        b += speedB;
        if (r < 0 || r > 1)
        {
            speedR *= -1;
        }
        if (g < 0 || g > 1)
        {
            speedG *= -1;
        }
        if (b < 0 || b > 1)
        {
            speedB *= -1;
        }
        obj->SetColor(Color(r, g, b, 1));
    }
};

Form1 form = seewk::WindowManager::CreateWindow<Form1>();

void OnStart()
{
    RunTest();
    std::cout << "program start\n";
}

void OnOver()
{
    std::cout << "over\n";
}