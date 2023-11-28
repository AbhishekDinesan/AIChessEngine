#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename T>
class Observer
{
public:
    virtual void notify(T &obj) = 0; // obj is the object that called the notify method
    virtual SubscriptionType subType() = 0;
    virtual ~Observer() = default;
};

enum class SubscriptionType
{
    All,
    MoveOnly
};

#endif