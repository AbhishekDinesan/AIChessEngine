#ifndef _ROOKPIECE_H_
#define _ROOKPIECE_H_

#include "AbstractPiece.h"

class Rook : public Piece
{
    bool canCastleFlag;

public:
    Rook(bool isWhite, bool isAlive, int x, int y, bool canCastleFlag);
    Rook(Rook &other);
    bool isValidMove(Move &m) override;
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
    void setX(int newX) override;
    void setY(int newY) override;
    bool canCastle() const;
    PieceEnum pieceType() override;
};

#endif