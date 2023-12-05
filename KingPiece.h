#ifndef _KINGPIECE_H_
#define _KINGPIECE_H_

#include "AbstractPiece.h"

class King : public Piece
{
    bool inCheck;
    bool beenMoved;

public:
    King(bool isWhite, bool isAlive, int x, int y, bool inCheck, bool beenMoved);
    King(King &other);
    bool isValidMove(Move &m) override;
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
    void setX(int newX) override;
    void setY(int newY) override;
    bool isInCheck() const;
    bool isFirstMove() const;
    PieceEnum pieceType() override;
};

#endif