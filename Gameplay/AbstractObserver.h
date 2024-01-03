#ifndef OBSERVER
#define OBSERVER

class Square;

class Observer
{
public:
    virtual void notify(Square &s) = 0;
    virtual ~Observer() = default;
};

#endif OBSERVER