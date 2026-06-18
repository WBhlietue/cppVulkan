#pragma once
#include<memory>
#include<vector>
#include<core/main/seewkObject.hpp>

class IWindow{
    
    public:
    IWindow(){}
    ~IWindow(){}
    IWindow(IWindow&) {}
    IWindow& operator=(IWindow&) {}
    virtual void Loop() = 0;
    virtual bool isWindow() = 0;
    virtual void OnLoop(float deltaTime) = 0;
    virtual void OnLoad() = 0;
    std::vector<std::unique_ptr<SeewkObject>> objects;
    SeewkObject& CreateSeewkObject(){
        std::unique_ptr<SeewkObject> ptr = std::make_unique<SeewkObject>();
        auto p = ptr.get();
        objects.push_back(std::move(ptr));
        return *p;
    }

    std::vector<std::unique_ptr<SeewkObject>> &GetObjects(){
        return objects;
    }

};