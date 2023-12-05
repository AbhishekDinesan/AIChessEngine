#include "AbstractPiece.h"
#include "RookPiece.h"
#include <memory>

Rook::Rook(bool isWhite, bool isAlive, int x, int y, bool canCastle) : Piece(isWhite, isAlive, x, y), canCastleFlag{canCastle} {}

Rook::Rook(Rook &other) : Piece(other.isWhite, other.isAlive, other.x, other.y) {}

bool Rook::getColour() const { return isWhite; }
bool Rook::getAlive() const { return isAlive; }
int Rook::getX() const { return x; }
int Rook::getY() const { return y; }
bool Rook::canCastle() const { return canCastleFlag; }
PieceEnum Rook::pieceType() { return PieceEnum::Rook; }

void Rook::setX(int newX)
{
    x = newX;
    return;
}

void Rook::setY(int newY)
{
    y = newY;
    return;
}

bool Rook::isValidMove(Move &m)
{
    if (isWhite)
    {
    }
    else
    {
    }
}