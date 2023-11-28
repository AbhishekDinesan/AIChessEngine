#ifndef _NONEPIECE_H_
#define _NONEPIECE_H_

#include "AbstractPiece.h"
#include "Move.h"

class None : public Piece {
 public:
    bool isValidMove(Move &m) override; // CHANGED THIS TO A BOOL, I THINK THIS IS BETTER
    bool getColour() const override;
    bool getAlive() const override;
    int getX() const override;
    int getY() const override;
};

#endif