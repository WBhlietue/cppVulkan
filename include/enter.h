#ifndef enter_h
#define enter_h
#include <functional>
#include<string>

struct Object
{
    int id;
    int width;
    int height;
    int x;
    int y;
    float borderRadius;
    glm::vec4 color;
    int texture_id;
    void SetTexture(int textureID);
};

void AddShape(Object object);
void MoveShape(Object object, int newX, int newY);
void VKAddOnClick(Object object, std::function<void()> onClick);
int VKLoadTexture(std::string path);
#endif