#include "AbstractPiece.h"
#include "PawnPiece.h"

Pawn::Pawn(bool isWhite, bool isAlive, bool firstMove, int x, int y) : isWhite{isWhite}, isAlive{isAlive}, firstMove{firstMove}, x{x}, y{y} {
}

bool Pawn::getColour() const { return isWhite; }
bool Pawn::getAlive() const { return isAlive; }
int Pawn::getX() const { return x; }
int Pawn::getY() const { return y; }
bool Pawn::getPassantability() const { return isEnPassantable; }
bool Pawn::isFirstMove() const { return firstMove; }
PieceEnum Pawn::pieceType() { return PieceEnum::Pawn; }

void Pawn::setX(int newX) { 
    x = newX; 
    return;
}

void Pawn::setY(int newY) { 
    y = newY; 
    return;
}

bool Pawn::isValidMove(Move &m) { 
    if (isWhite)
    {
        
    }
    else 
    {

    }
}