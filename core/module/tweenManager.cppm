module;

export module seewk.tween;

import seewk.ease;

struct TweenData
{
    float duration;
    AnimationEase ease;
    std::function<void(float step)> onUpdate;
    std::function<void()> onComplete;
    float count = 0;
    virtual void OnUpdate() = 0;
    virtual void OnFinalUpdate() = 0;
    TweenData &SetEase(AnimationEase e)
    {
        ease = e;
        return *this;
    }
    TweenData &SetUpdate(std::function<void(float step)> e)
    {
        onUpdate = e;
        return *this;
    }
    TweenData &SetComplete(std::function<void()> e)
    {
        onComplete = e;
        return *this;
    }
    bool Update(float delta)
    {
        count += delta;
        if (count >= duration)
        {
            // onUpdate(to);
            OnFinalUpdate();
            onComplete();
            return true;
        }
        OnUpdate();
        // onUpdate(from + (count / duration) * dataDelta);
        return false;
    }
};

struct NumberTweenData : TweenData
{
    float from;
    float to;
    float dataDelta;

    void Init(float f, float t, float d)
    {
        from = f;
        to = t;
        duration = d;
        dataDelta = t - f;
    }
    void OnUpdate() override
    {
        onUpdate(from + ease(count / duration) * dataDelta);
    }
    void OnFinalUpdate() override
    {
        onUpdate(to);
    }
};

export class TweenManager
{
    std::vector<std::unique_ptr<TweenData>> tweenDatas;

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
            if (tweenDatas[i].get()->Update(delta))
            {
                tweenDatas.erase(tweenDatas.begin() + i);
                i--;
            }
        }
    }
    NumberTweenData &NumberTween(float from, float to, float duration)
    {
        std::unique_ptr<NumberTweenData> ptr = std::make_unique<NumberTweenData>();
        auto p = ptr.get();
        p->Init(from, to, duration);
        tweenDatas.push_back(std::move(ptr));
        return *p;
        // tweenDatas.push_back(NumberTweenData(from, to, duration));
        // int size = tweenDatas.size();
        // tweenDatas[size - 1].SetUpdate(onUpdate);
        // tweenDatas[size - 1].SetComplete(onComplete);
        // tweenDatas[size - 1].SetEase(ease);
    }
    static TweenManager &GetInstance()
    {
        static TweenManager instance;
        return instance;
    }
};