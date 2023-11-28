#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "AbstractObserver.h"
class Cell;

class TextDisplay : public Observer<Cell>
{
    std::vector<std::vector<char>> theDisplay;
    const int gridSize;

public:
    TextDisplay(int n);

    // void notify(Cell &c) override;
    // SubscriptionType subType() override;

    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif