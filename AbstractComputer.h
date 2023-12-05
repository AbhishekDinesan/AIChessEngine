#include "AbstractPlayer.h"
#include "Board.h"

#ifndef _COMPUTER_H_
#define _COMPUTER_H_

class Computer : public AbstractPlayer
{
protected:
    Computer(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : AbstractPlayer(isWhite, isHuman, isInCheck, myboard) {}

public:
    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) = 0;
    virtual bool getIsHuman() = 0;
    virtual bool getColour() = 0;
    virtual void setBoard(Board* b) = 0;
    virtual ~Computer() = default;
};

#endif
