#ifndef enter_h
#define enter_h

struct Object
{
    int id;
    int width;
    int height;
    int x;
    int y;
    float borderRadius;
    glm::vec4 color;
};

void AddShape(Object object);
void MoveShape(Object object, int newX, int newY);

#endif