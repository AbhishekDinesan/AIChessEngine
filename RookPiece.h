#ifndef _ROOKPIECE_H_
#define _ROOKPIECE_H_

#include "AbstractPiece.h"

class Rook : public Piece
{
    bool isWhite;
    bool isAlive;
    bool canCastleFlag;
    // Move nextMove {};
    int x, y;

public:
    Rook(bool isWhite, bool isAlive, bool canCastleFlag, int x, int y);
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