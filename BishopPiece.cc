#include "AbstractPiece.h"
#include "BishopPiece.h"


Bishop::Bishop(bool isWhite, bool isAlive, int x, int y) : isWhite{isWhite}, isAlive{isAlive}, x{x}, y{y} {}

bool Bishop::getColour() const { return isWhite; }
bool Bishop::getAlive() const { return isAlive; }
int Bishop::getX() const { return x; }
int Bishop::getY() const { return y; }
PieceEnum Bishop::pieceType() { return PieceEnum::Bishop; }

void Bishop::setX(int newX)
{
    x = newX;
    return;
}

void Bishop::setY(int newY)
{
    y = newY;
    return;
}

bool Bishop::isValidMove(Move &m)
{
    if (isWhite)
    {
    }
    else
    {
    }
}