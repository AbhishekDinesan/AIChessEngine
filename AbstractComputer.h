#include "AbstractPlayer.h"
#include "Board.h"

#ifndef _COMPUTER_H_
#define _COMPUTER_H_

class Computer : public AbstractPlayer
{
    Computer(Board *myboard)
    {
        isHuman = false;
        isInCheck = false;
        board = myboard;
    }

protected:
    Computer() {}

public:
    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) = 0;
    virtual ~Computer() = default;
};

#endif
