#ifndef _QUEENPIECE_H_
#define _QUEENPIECE_H_

#include "AbstractPiece.h"

class Queen : public Piece
{
public:
    Queen(bool isWhite, bool isAlive, int x, int y);
    Queen(Queen &other);
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