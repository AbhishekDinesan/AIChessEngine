#include "AbstractPiece.h"
#include "NonePiece.h"

NonePc::NonePc(int x, int y) : Piece(true, true, x, y) {}
bool NonePc::isValidMove(Move &m) { return true; }
bool NonePc::getColour() const { return isWhite; }
bool NonePc::getAlive() const { return isAlive; }
int NonePc::getX() const { return x; }
int NonePc::getY() const { return y; }
PieceEnum NonePc::pieceType() { return PieceEnum::NonePc; }

NonePc::NonePc(NonePc &other) : Piece(other.isWhite, other.isAlive, other.x, other.y) {}

void NonePc::setX(int newX)
{
    x = newX;
    return;
}

void NonePc::setY(int newY)
{
    y = newY;
    return;
}
