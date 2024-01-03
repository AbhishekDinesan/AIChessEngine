#include "AbstractPiece.h"
#include "KingPiece.h"

King::King(bool isWhite, bool isAlive, int x, int y, bool inCheck, bool beenMoved) : Piece(isWhite, isAlive, x, y), inCheck{inCheck}, beenMoved{beenMoved} {}

King::King(King &other) : Piece(other.isWhite, other.isAlive, other.x, other.y) {}

bool King::getColour() const { return isWhite; }
bool King::getAlive() const { return isAlive; }
int King::getX() const { return x; }
int King::getY() const { return y; }
bool King::isInCheck() const { return inCheck; }
bool King::isFirstMove() const { return !beenMoved; }
PieceEnum King::pieceType() { return PieceEnum::King; }

void King::setX(int newX)
{
    x = newX;
    return;
}

void King::setY(int newY)
{
    y = newY;
    return;
}

bool King::isValidMove(Move &m)
{
    if (isWhite)
    {
    }
    else
    {
    }
}