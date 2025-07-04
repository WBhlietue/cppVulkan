#include <core/core.h>
#include <string>

static int objectID = 0;

Object DrawRectangle(int width, int height, int x, int y, glm::vec4 color, float borderRadius)
{
    Object object;
    object.id = objectID++;
    object.width = width;
    object.height = height;
    object.x = x;
    object.y = y;
    object.color = color;
    object.borderRadius = borderRadius;
    AddShape(object);
    return object;
}
void AddOnClick(Object object, std::function<void()> onClick)
{
    VKAddOnClick(object, onClick);
}

int Load_Texture(std::string path){
    return VKLoadTexture(path);
}