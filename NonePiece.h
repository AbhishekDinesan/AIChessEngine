#ifndef _NONEPIECE_H_
#define _NONEPIECE_H_

#include "AbstractPiece.h"

class None : public Piece
{
public:
    None(int x, int y);
    None(None &other);
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