#ifndef _NONEPIECE_H_
#define _NONEPIECE_H_

#include "AbstractPiece.h"

class NonePc : public Piece
{
public:
    NonePc(int x, int y);
    NonePc(NonePc &other);
    bool isValidMove(Move &m) override; // CHANGED THIS TO A BOOL, I THINK THIS IS BETTER
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
    void setX(int newX) override;
    void setY(int newY) override;
    PieceEnum pieceType() override;
};

#endif