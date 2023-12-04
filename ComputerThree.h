#ifndef COMPUTER_THREE_H
#define COMPUTER_THREE_H

#include "AbstractComputer.h"
#include "Move.h"

class ComputerThree : public Computer
{
public:
    ComputerThree(bool isWhite, bool isHuman, bool isInCheck, Board *myboard);

    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) override;

private:
    // Add any private member variables or functions here if needed
};

#endif // COMPUTER_THREE_H
