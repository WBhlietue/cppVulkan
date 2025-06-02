#include <core/core.h>

static int objectID = 0;

Object DrawRectangle(int width, int height, int x, int y, glm::vec3 color)
{
    Object object;
    object.id = objectID++;
    object.width = width;
    object.height = height;
    object.x = x;
    object.y = y;
    object.color = color;
    AddShape(object);
    return object;
}