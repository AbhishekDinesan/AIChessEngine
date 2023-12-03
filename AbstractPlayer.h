#include "Move.h"
#include "Board.h"

#ifndef _ABSTRACTPLAYER_H_
#define _ABSTRACTPLAYER_H_

class AbstractPlayer
{
protected:
  AbstractPlayer(bool isHuman, bool isInCheck, Board *board) : isHuman{isHuman}, isInCheck{isInCheck}, board{board} {};

protected:
  bool isHuman;
  bool isInCheck;
  Board *board;

public:
  virtual void makeMove(int startFile, int startRank, int endFile, int endRank) = 0;
  virtual ~AbstractPlayer() = default;
};
#endif
