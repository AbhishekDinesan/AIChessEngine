#ifndef COMPUTERTWO_H
#define COMPUTERTWO_H

#include "AbstractComputer.h"
#include "Move.h"
#include "Board.h"
#include <vector>

class ComputerTwo : public Computer
{
public:
    ComputerTwo(bool isWhite, bool isHuman, bool isInCheck, Board *myboard);

    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) override;

private:
    // Add any private member variables or functions here if needed
};

#endif // COMPUTERTWO_H
