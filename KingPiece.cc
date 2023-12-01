#include "AbstractPiece.h"
#include "KingPiece.h"

King::King(bool isWhite, bool isAlive, bool inCheck, bool beenMoved, int x, int y) : isWhite{isWhite}, isAlive{isAlive}, inCheck{inCheck}, beenMoved{beenMoved}, x{x}, y{y} {}

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