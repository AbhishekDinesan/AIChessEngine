// square.cc
#include <iostream>
#include "square.h"
#include "PawnPiece.h"
#include "RookPiece.h"
#include "QueenPiece.h"
#include "KingPiece.h"
#include "BishopPiece.h"
#include "KnightPiece.h"
#include "NonePiece.h"
// #include "NonePiece.h"
using namespace std;

// Default constructor for square
Square::Square() : x(0), y(0), occupied(false), occupiedBy(nullptr)
{
    // None *emptyPiece = new None();
}

Square::Square(const Square &other) : x(other.x), y(other.y), occupied(nullptr), occupiedBy(nullptr)
{

    if (other.occupiedBy)
    {
        if (other.occupiedBy->pieceType() == PieceEnum::Pawn)
        {
            Pawn *pawn = dynamic_cast<Pawn *>(other.occupiedBy);
            if (pawn)
            {
                occupiedBy = new Pawn(*pawn);
            }
        }
        if (other.occupiedBy->pieceType() == PieceEnum::Rook)
        {
            Rook *rook = dynamic_cast<Rook *>(other.occupiedBy);
            if (rook)
            {
                occupiedBy = new Rook(*rook);
            }
        }
        if (other.occupiedBy->pieceType() == PieceEnum::Queen) // Queen
        {
            Queen *queen = dynamic_cast<Queen *>(other.occupiedBy);
            if (queen)
            {
                occupiedBy = new Queen(*queen);
            }
        }
        if (other.occupiedBy->pieceType() == PieceEnum::King) // King
        {

            King *king = dynamic_cast<King *>(other.occupiedBy);
            if (king)
            {
                occupiedBy = new King(*king);
            }
        }
        if (other.occupiedBy->pieceType() == PieceEnum::Bishop) // Bishop
        {
            Bishop *bishop = dynamic_cast<Bishop *>(other.occupiedBy);
            if (bishop)
            {
                occupiedBy = new Bishop(*bishop);
            }
        }
        if (other.occupiedBy->pieceType() == PieceEnum::Knight) // Knight
        {
            Knight *knight = dynamic_cast<Knight *>(other.occupiedBy);
            if (knight)
            {
                occupiedBy = new Knight(*knight);
            }
        }
        else

        {
            None *none = dynamic_cast<None *>(other.occupiedBy);
            if (none)
            {
                occupiedBy = new None(*none);
            }
        }
    }
}

// Destructor for square
Square::~Square()
{
    for (auto obs : observers)
    {
        delete obs;
    }
}

// returns the X value of the square
int Square::getX()
{
    return x;
}

// returns the Y value of the square
int Square::getY()
{
    return y;
}

void Square::setCoords(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Square::getOccupied()
{
    return occupied;
}

Piece *Square::getOccupyingPc()
{
    return this->occupiedBy;
}

// the square will notify all of the observers about a change that has happened on this
//     square.
void Square::notifyObservers(Square &s)
{
    for (Observer *obs : observers)
    {
        obs->notify(s);
    }
}

void Square::attach(Observer *o)
{
    observers.emplace_back(o);
}

// setPiece(piece) sets the piece to the current square, and
//     and notifies the observers of a change to the piece
//  NOTE: THIS IS NOT IN THE UML, WILL NEED TO INCLUDE IN REPORT
void Square::setPiece(Piece *piece)
{
    occupiedBy = piece;
    notifyObservers(*this);
}
