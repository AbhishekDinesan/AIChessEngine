#include "AbstractPiece.h"
#include "KnightPiece.h"

Knight::Knight(bool isWhite, bool isAlive, int x, int y) : isWhite{isWhite}, isAlive{isAlive}, x{x}, y{y} {}

bool Knight::getColour() const { return isWhite; }
bool Knight::getAlive() const { return isAlive; }
int Knight::getX() const { return x; }
int Knight::getY() const { return y; }

void Knight::setX(int newX)
{
    x = newX;
    return;
}

void Knight::setY(int newY)
{
    y = newY;
    return;
}

bool Knight::isValidMove(Move &m)
{
    if (isWhite)
    {
    }
    else
    {
    }
}