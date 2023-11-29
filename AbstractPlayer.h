#include "Move.h"

#ifndef _ABSTRACTPLAYER_H_
#define _ABSTRACTPLAYER_H_

class AbstractPlayer
{
  bool isHuman;
  bool isInCheck;

public:
  virtual void makeMove(Move &m) = 0;
  virtual ~AbstractPlayer() = default;
};
#endif
