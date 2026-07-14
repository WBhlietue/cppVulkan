module;

#include <functional>

export module seewk.ease;

export using AnimationEase = std::function<float(float)>;

export struct Ease
{
    static float Linear(float value)
    {
        return value;
    };
    static float Square(float value){
        return value*value;
    }
};