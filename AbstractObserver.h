#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Square;

enum class SubscriptionType { All, MoveOnly };

class Observer {
public:
    virtual void notify(Square &s) = 0;
    virtual SubscriptionType subType() = 0;
    virtual ~Observer() = default;
};

#endif
