#ifndef COMPUTER_H
#define COMPUTER_H

#include "AbstractComputer.h"
#include "Move.h"

class ComputerThree : public Computer
{
public:
    ComputerThree(bool isWhite, bool isHuman, bool isInCheck, Board *myboard);
    virtual bool getIsHuman() override;
    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) override;
    virtual void setBoard(Board *b) override;
    virtual bool getColour() override;

private:
    // Add any private member variables or functions here if needed
};

#endif