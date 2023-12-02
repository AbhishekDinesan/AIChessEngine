#include "AbstractPlayer.h"

#ifndef _COMPUTER_H_
#define _COMPUTER_H_

class Computer : public AbstractPlayer
{
public:
    virtual void makeMove(Move &m) override = 0;
    virtual ~Computer() = default;
};

#endif
