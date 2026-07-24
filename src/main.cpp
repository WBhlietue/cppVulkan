#include <core/main/seewkObject.hpp>
#include <core/core.h>
import seewk;
import seewk.tween;


TweenManager &tManager = TweenManager::GetInstance();

class Form1 : public seewk::main::Form
{
    public:
    int border = 30;
    int borderSpeed = 1;
    SeewkObject *obj = nullptr;
    Vec2 objPosOffset;
    int texture = -1;

    void PreLoad() override
    {
        texture = GetTexture("assets/moon.png");
    }

    void OnLoad() override
    {
        obj = &CreateObject()
                   .SetPosition(Vec2(0, 0))
                   .SetSize(Vec2(500, 500))
                   .SetColor(Color(1, 1, 1, 1))
                   .SetBorderRadius(border)
                   .SetClick([this](int button)
                             { std::cout << "click\n";
                                this->Scale(); })
                   .SetMouseDown([this](int button)
                                 { this->objPosOffset = GetMousePosition() - this->obj->GetPosition(); })
                   .SetDrag([this](int button)
                            {
                                Vec2 mousePosition = GetMousePosition();
                                this->obj->SetPosition(mousePosition - this->objPosOffset); })
                   .SetTexture(texture);
    }
    void OnLoop(float deltaTime) override
    {
        border += borderSpeed;
        if (border < 10 || border > 100)
        {
            borderSpeed *= -1;
        }
        obj->SetBorderRadius(border);
    }

public:
    void Scale()
    {
        tManager.NumberTween(0, 500, 0.5).SetUpdate([this](float x)
                                                    {
                int size = x;
                obj->SetSize({size, size}); })
            .SetComplete([this]
                         { obj->SetSize({500, 500}); });
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