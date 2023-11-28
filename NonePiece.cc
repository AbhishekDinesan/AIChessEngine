#include "AbstractPiece.h"
#include "NonePiece.h"

None::None() {}
bool None::isValidMove(Move &m) { return true; }
bool None::getColour() const { return isWhite; }
bool None::getAlive() const { return isAlive; }
int None::getX() const { return position.x; }
int None::getY() const { return position.y; }
