#include <core/paint.h>
#include <iostream>
#include <vulkan/vulkan.h>

using namespace std;
void Paint(JSON json)
{
    for (auto &item : json.items())
    {
        JSON content = item.value();
        cout << content["type"] << endl;
    }
}