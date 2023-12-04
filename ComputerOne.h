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

    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) override;
};

#endif // COMPUTERONE_H