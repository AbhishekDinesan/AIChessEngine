#ifndef _KNIGHTPIECE_H_
#define _KNIGHTPIECE_H_

#include "AbstractPiece.h"

class Knight : public Piece
{
public:
    Knight(bool isWhite, bool isAlive, int x, int y);
    Knight(Knight &other);
    bool isValidMove(Move &m) override;
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
    void setX(int newX) override;
    void setY(int newY) override;
    PieceEnum pieceType() override;
};

#endif