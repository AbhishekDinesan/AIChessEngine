#include "AbstractPiece.h"
#include "NonePiece.h"

None::None(int x, int y) : Piece(true, true, x, y) {} 
bool None::isValidMove(Move &m) { return true; }
bool None::getColour() const { return isWhite; }
bool None::getAlive() const { return isAlive; }
int None::getX() const { return x; }
int None::getY() const { return y; }
PieceEnum None::pieceType() { return PieceEnum::None; }

void None::setX(int newX) { 
    x = newX; 
    return;
}

void None::setY(int newY) { 
    y = newY;
    return;
 }
