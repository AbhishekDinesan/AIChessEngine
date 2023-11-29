#ifndef _KINGPIECE_H_
#define _KINGPIECE_H_

#include "AbstractPiece.h"

class King : public Piece
{
    bool isWhite;
    bool isAlive;
    bool inCheck;
    bool beenMoved;
    // Move nextMove {};
    int x, y;

public:
    King(bool isWhite, bool isAlive, bool inCheck, bool beenMoved, int x, int y);
    bool isValidMove(Move &m) override;
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
    void setX(int newX) override;
    void setY(int newY) override;
    bool isInCheck() const;
    bool isFirstMove() const;
};

#endif