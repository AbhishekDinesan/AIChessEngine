#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Square;

class Observer
{
public:
    virtual void notify(Square &s) = 0;
    virtual ~Observer() = default;
};

#endif
