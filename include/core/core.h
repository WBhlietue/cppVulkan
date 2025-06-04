#ifndef core_h
#define core_h

#include <glm/glm.hpp>
#include <enter.h>
#include <functional>

Object DrawRectangle(int width, int height, int x, int y, glm::vec4 color, float borderRadius);
void AddOnClick(Object object, std::function<void()> onClick);

#endif