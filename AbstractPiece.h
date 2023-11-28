#ifndef _ABSTRACTPIECE_H_
#define _ABSTRACTPIECE_H_

#include "Move.h" 

enum class PieceEnum {None, Pawn, Rook, Knight, Bishop, Queen, King};

class Piece {
    bool isWhite;
    bool isAlive;
    Move nextMove {};
    struct coords { int x, y; };
    coords position;
 public:
  virtual bool isValidMove(Move &m) = 0; // CHANGED TO A BOOL
  virtual bool getColour() const;
  virtual bool getAlive() const;
  virtual int getX() const;
  virtual int getY() const;
  virtual ~Piece() = default;
};

#endif
