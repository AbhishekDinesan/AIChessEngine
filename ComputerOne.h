#ifndef COMPUTERONE_H
#define COMPUTERONE_H

#include "AbstractComputer.h"
#include "AbstractPiece.h"
#include "Move.h"
#include "Board.h"
#include <vector>

class ComputerOne : public Computer
{
public:
    ComputerOne(bool isWhite, bool isHuman, bool isInCheck, Board *myboard);
    virtual bool getIsHuman() override;
    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) override;
    virtual void setBoard(Board* b) override;
    virtual bool getColour() override;
};

#endif // COMPUTERONE_H