
#ifndef _ABSTRACTPIECE_H_
#define _ABSTRACTPIECE_H_

enum class PieceEnum { None, Pawn, Rook, Knight, Bishop, Queen, King };

class Piece {
    bool isWhite;
    bool isAlive;
    Move nextMove {};
 public:
  virtual void isValidMove(Move &m) = 0;
  virtual bool getColour() = 0;
  virtual bool getAlive() = 0;
  virtual int getX() = 0;
  virtual int getY() = 0;
  virtual ~Piece() = default;
};

#endif
