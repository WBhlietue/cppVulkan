#include <cmath>
#include <core/main/seewkObject.hpp>
#include <random>
import seewk;

const float PI = 3.1415926;

float GetRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

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
    SeewkObject *obj2 = nullptr;

    bool change = false;
    Vec2 obj2PosOffset;

    void OnLoad() override
    {

        obj = &CreateObject()
                   .SetPosition(Vec2(0, 0))
                   .SetSize(Vec2(100, 100))
                   .SetColor(Color(r, g, b, 1))
                   .SetBorderRadius(border)
                   .SetMouseEnter([this]()
                                  { this->change = true; })
                   .SetMouseExit([this]()
                                 { this->change = false; });

        obj2 = &CreateObject()
                    .SetPosition(Vec2(100, 0))
                    .SetSize(Vec2(200, 200))
                    .SetColor(Color(r, g, b, 1))
                    .SetBorderRadius(border)
                    .SetClick([this](int button)
                              { this->obj2->SetColor({GetRandomFloat(0.0f, 1.0f),
                                                      GetRandomFloat(0.0f, 1.0f),
                                                      GetRandomFloat(0.0f, 1.0f),
                                                      1}); })
                    .SetMouseDown([this](int button)
                                  { this->obj2PosOffset = GetMousePosition() - this->obj2->GetPosition(); })
                    .SetDrag([this](int button)
                             {
                                Vec2 mousePosition = GetMousePosition();
                                this->obj2->SetPosition(mousePosition - this->obj2PosOffset); });
    }
    void OnLoop(float deltaTime) override
    {
        // std::cout << 1 / deltaTime << std::endl;
        // angle += speed;
        // int x = sin(angle * PI / 180.0) * radius;
        // int y = cos(angle * PI / 180.0) * radius;
        // obj->SetPosition(Vec2(x, y));
        if (!change)
        {
            return;
        }
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
    std::cout << "program start\n";
}

void OnOver()
{
    std::cout << "over\n";
}