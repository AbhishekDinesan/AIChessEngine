#include "Move.h"
#include "Board.h"

#ifndef _ABSTRACTPLAYER_H_
#define _ABSTRACTPLAYER_H_

class AbstractPlayer
{
protected:
  bool isHuman;
  bool isInCheck;
  Board *board;

public:
  virtual void makeMove(int startFile, int startRank, int endFile, int endRank) = 0;
  virtual ~AbstractPlayer() = default;
};
#endif
