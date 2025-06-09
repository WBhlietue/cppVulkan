#ifndef objectActions_h
#define objectActions_h

#include<functional>

struct Object_OnClick
{
    int id;
    std::function<void()> callback;
    void Check(double x, double y);
};
struct Object_OnMouseEnter
{
    int id;
    std::function<void()> callback;
    bool isIn = false;
    void Check(double x, double y);
};
struct Object_OnMouseLeave
{
    int id;
    std::function<void()> callback;
    bool isIn = false;
    void Check(double x, double y);
};
struct Object_OnMouseStay
{
    int id;
    std::function<void()> callback;
    bool isIn = false;
    void Check(double x, double y);
};

#endif