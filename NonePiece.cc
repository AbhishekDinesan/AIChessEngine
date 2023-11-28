#include "AbstractPiece.h"
#include "NonePiece.h"

bool Piece::isValidMove(Move &m) { return true; }
bool Piece::getColour() const { return isWhite; }
bool Piece::getAlive() const { return isAlive; }
int Piece::getX() const { return position.x; }
int Piece::getY() const { return position.y; }
