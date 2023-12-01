#include "AbstractPiece.h"
#include "QueenPiece.h"

Queen::Queen(bool isWhite, bool isAlive, int x, int y) : isWhite{isWhite}, isAlive{isAlive}, x{x}, y{y} {}

bool Queen::getColour() const { return isWhite; }
bool Queen::getAlive() const { return isAlive; }
int Queen::getX() const { return x; }
int Queen::getY() const { return y; }
PieceEnum Queen::pieceType() { return PieceEnum::Queen; }

void Queen::setX(int newX)
{
    x = newX;
    return;
}

void Queen::setY(int newY)
{
    y = newY;
    return;
}

bool Queen::isValidMove(Move &m)
{
    if (isWhite)
    {
    }
    else
    {
    }
}