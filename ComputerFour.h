#ifndef COMPUTER_FOUR_H
#define COMPUTER_FOUR_H

#include "AbstractComputer.h"
#include "PawnPiece.h"
#include <map>

class ComputerFour : public Computer
{
public:
    ComputerFour(bool isWhite, bool isHuman, bool isInCheck, Board *myboard);

    virtual void makeMove(int startFile, int startRank, int endFile, int endRank) override;

private:
    // Add any private member variables or functions here if needed
};

#endif // COMPUTER_FOUR_H
