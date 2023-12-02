#ifndef _ABSTRACTPIECE_H_
#define _ABSTRACTPIECE_H_

#include "Move.h"

enum class PieceEnum
{
  None, 
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King
};

class Piece
{
  bool isWhite;
  bool isAlive;
  // Move nextMove {}
  int x, y;

public:
  virtual bool isValidMove(Move &m) = 0; // CHANGED TO A BOOL
  virtual bool getColour() const = 0;
  virtual bool getAlive() const = 0;
  virtual int getX() const = 0;
  virtual int getY() const = 0;
  virtual void setX(int newX) = 0;
  virtual void setY(int newY) = 0;
  virtual PieceEnum pieceType() = 0;
  virtual ~Piece() = default;
};

#endif
