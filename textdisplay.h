#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "AbstractObserver.h"
class Square;

class TextDisplay : public Observer
{
    std::vector<std::vector<char>> theDisplay;

public:
    TextDisplay();
    void notify(Square &s) override;
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif