#ifndef _PAWNPIECE_H_
#define _PAWNPIECE_H_

#include "AbstractPiece.h"

class Pawn : public Piece {
    bool isWhite;
    bool isAlive;
    bool isEnPassantable;
    bool beenMoved;
    //Move nextMove {};
    int x, y;
 public:
    Pawn(bool isWhite, bool isAlive, bool beenMoved, int x, int y);
    bool isValidMove(Move &m) override;
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
    void setX(int newX) override;
    void setY(int newY) override;
    bool getPassantability() const;
    bool isFirstMove() const;
};

#endif