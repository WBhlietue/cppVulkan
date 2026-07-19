#include <cmath>
#include <core/main/seewkObject.hpp>
#include <random>
#include <core/core.h>
import seewk;
import seewk.tween;
import seewk.ease;

const float PI = 3.1415926;
int texture1 = -1;

TweenManager &tManager = TweenManager::GetInstance();

void LoadTextures()
{
}

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
    float r = 1, g = 1, b = 1;
    float speedR = 0.13f;
    float speedG = 0.17f;
    float speedB = 0.29f;
    SeewkObject *obj = nullptr;
    SeewkObject *obj2 = nullptr;

    bool change = false;
    Vec2 obj2PosOffset;

    void PreLoad() override
    {
        texture1 = GetTexture("assets/moon.png");
    }

    void OnLoad() override
    {
        SetWindowSize(100, 100);
        Init();
        // for(int i = -400; i < 400; i++){
        //     for(int j = -300; j < 300; j++){
        //         CreateObject().SetPosition(Vec2(i, j)).SetSize(Vec2(10, 10)).SetColor(Color(GetRandomFloat(0.0f, 1.0f),GetRandomFloat(0.0f, 1.0f),GetRandomFloat(0.0f, 1.0f),1));
        //     }
        // }

        // obj = &CreateObject()
        //            .SetPosition(Vec2(300, 200))
        //            .SetSize(Vec2(100, 100))
        //            .SetColor(Color(r, g, b, 1))
        //            .SetBorderRadius(border)
        //            .SetMouseEnter([this]()
        //                           { this->change = true; })
        //            .SetMouseExit([this]()
        //                          { this->change = false; });

        obj2 = &CreateObject()
                    .SetPosition(Vec2(0, 0))
                    .SetSize(Vec2(500, 500))
                    .SetColor(Color(r, g, b, 1))
                    .SetBorderRadius(border)
                    .SetClick([this](int button)
                              { this->obj2->SetColor({GetRandomFloat(0.0f, 1.0f),
                                                      GetRandomFloat(0.0f, 1.0f),
                                                      GetRandomFloat(0.0f, 1.0f),
                                                      1}); this->Init(); })
                    .SetMouseDown([this](int button)
                                  { this->obj2PosOffset = GetMousePosition() - this->obj2->GetPosition(); })
                    .SetDrag([this](int button)
                             {
                                Vec2 mousePosition = GetMousePosition();
                                this->obj2->SetPosition(mousePosition - this->obj2PosOffset); })
                    .SetTexture(texture1);
        // tManager.NumberTween(0, 100, 0.5)
        //     .SetEase(Ease::Square)
        //     .SetUpdate([this](float x)
        //                { this->obj2->SetSize({500 * x / 100, 500 * x / 100}); })
        //     .SetComplete([]
        //                  { std::cout << "tween Done\n"; });
    }
    void OnLoop(float deltaTime) override
    {
        // std::cout << "Loop per seconds: " <<  1 / deltaTime << std::endl;
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

public:
    void Init()
    {
        tManager.NumberTween(0, 1000, 0.5).SetEase(Ease::Square).SetUpdate([this](float x)
                                                                           {
                int size = x;
                this->SetWindowPosition(960-size/2, 540-size/2);
                this->SetWindowSize(size, size); })
            .SetComplete([this]
                         { this->SetWindowSize(1000, 1000); });
    }
};


void OnStart()
{
    seewk::WindowManager::CreateWindow<Form1>();
}

void OnOver()
{
    std::cout << "over\n";
}