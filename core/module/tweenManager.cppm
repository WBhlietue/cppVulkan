module;

export module seewk.tween;

struct TweenData
{
    int from;
    int to;
    float duration;
    int ease;
    std::function<void(int step)> onUpdate;
    std::function<void()> onComplete;
    float dataDelta;

    float count = 0;
    bool Update(float delta)
    {
        count += delta;
        if (count >= duration)
        {
            onUpdate(to);
            onComplete();
            return true;
        }
        onUpdate(from + (count / duration) * dataDelta);
        return false;
    }
};

export class TweenManager
{
    std::vector<TweenData> tweenDatas;

public:
    void Test()
    {
        std::cout << "HIHIIIII\n";
    }
    void Loop(float delta)
    {
        // std::cout << tweenDatas.size() << std::endl;
        for (int i = 0; i < tweenDatas.size(); i++)
        {
            if (tweenDatas[i].Update(delta))
            {
                tweenDatas.erase(tweenDatas.begin() + i);
                i--;
            }
        }
    }
    void NumberTween(int from, int to, float duration, int ease, std::function<void(int step)> onUpdate, std::function<void()> onComplete)
    {
        float delta = to - from;
        tweenDatas.push_back({from, to, duration, ease, onUpdate, onComplete, delta});
    }
    static TweenManager &GetInstance()
    {
        static TweenManager instance;
        return instance;
    }
};