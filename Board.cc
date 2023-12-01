#include <stdexcept>
#include "Board.h"
#include "NonePiece.h"
#include "square.h"
#include "stdexcept"
#include "textdisplay.h"
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include <stdio.h>

// constructor for Board
Board::Board() : squares(8, std::vector<Square>(8))
{
    TextDisplay *newTextDisplay = new TextDisplay;
    td = newTextDisplay;
    
    // Piece *blackLRook = new Rook(false, true, 0, 0);
    // Piece *blackRiRook = new Rook(false, true, 7, 0);
    // squares[0][0].setPiece(blackLRook);
    // squares[7][0].setPiece(blackRiRook);

    // Piece *blackLKnight = new Knight(false, true, 1, 0);
    // Piece *blackRKnight = new Knight(false, true, 6, 0);
    // squares[1][0].setPiece(blackLKnight);
    // squares[6][0].setPiece(blackRKnight);

    // Piece *blackLBishop = new Bishop(false, true, 2, 0);
    // Piece *blackRBishop = new Bishop(false, true, 5, 0);
    // squares[2][0].setPiece(blackLBishop);
    // squares[5][0].setPiece(blackRBishop);

    // Piece *blackQueen = new Queen(false, true, 4, 0);
    // squares[4][0].setPiece(blackQueen);

    // Piece *blackKing = new King(false, true, 5, 0);
    // squares[5][0].setPiece(blackKing);

    // PAWNS
    for (int cols = 0; cols < 8; ++cols) {
        Piece *blackPawn = new Pawn(false, true, false, cols, 1);
    }
    
    // EMPTY SPACES
    for (int x = 2; x < 6; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            None *emptypiece = new None(x, y);
            squares[x][y].setPiece(emptypiece);
        }
    }

    for (int cols = 0; cols < 8; ++cols) {
        Piece *whitePawn = new Pawn(true, true, false, cols, 6);
    }

    // Rook *whiteLRook = new Rook(true, true, 0, 7);
    // Rook *whiteRiRook = new Rook(true, true, 7, 7);
    // squares[0][7].setPiece(whiteLRook);
    // squares[7][7].setPiece(whiteRiRook);

    // Knight *whiteLKnight = new Knight(true, true, 1, 7);
    // Knight *whiteRKnight = new Knight(true, true, 6, 7);
    // squares[1][7].setPiece(whiteLKnight);
    // squares[6][7].setPiece(whiteRKnight);

    // Bishop *whiteLBishop = new Bishop(true, true, 2, 7);
    // Bishop *whiteRBishop = new Bishop(true, true, 5, 7);
    // squares[2][7].setPiece(whiteLBishop);
    // squares[5][7].setPiece(whiteRBishop);

    // Queen *whiteQueen = new Queen(true, true, 4, 7);
    // squares[4][7].setPiece(whiteQueen);

    // Queen *whiteKing = new King(true, true, 5, 7);
    // squares[5][7].setPiece(whiteKing);

    

    std::cout << "do we get this far" << std::endl;
}

// destructor for Board.
Board::~Board()
{
    for (int x = 0; x < squares.size(); ++x)
    {
        for (int y = 0; y < squares[x].size(); ++y)
        {
            delete squares[x][y].getOccupyingPc();
            squares[x][y].setPiece(nullptr);
        }
    }
}

void Board::addPiece(int x, int y, Piece &p)
{
    // make sure that coordinates are within bounds
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        throw std::out_of_range("Coordinates are out of the board's bounds.");
    }

    squares[x][y].setPiece(&p);
}

// delete the piece at the index, and replace with a NonePiece.
void Board::removePiece(int x, int y)
{
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        throw std::out_of_range("Coordinates are out of the board's bounds.");
    }
    Piece *nonePiece = new None(x, y);
    delete squares[x][y].getOccupyingPc();
    squares[x][y].setPiece(nonePiece);
}

bool Board::isOccupied(int x, int y)
{
    // Check if the coordinates are within the bounds of the board
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        throw std::out_of_range("Coordinates are out of the board's bounds.");
    }

    // Assuming `squares` is a 2D vector and getPiece() returns a Piece*
    Piece *currentPiece = squares[x][y].getOccupyingPc();

    return currentPiece != nullptr && dynamic_cast<None *>(currentPiece) == nullptr;
}

// CANNOT BE IMPLEMENTED YET, Need pieces to be done.
bool Board::isCovered(int x, int y)
{
    return false;
}

Piece *Board::getPiecePtr(int x, int y) {
    Piece *p = squares[x][y].getOccupyingPc(); 
    return p; 
}

std::ostream &operator<<(std::ostream &out, const Board &b)
{
    out << *(b.td);
    return out;
}

//IMPLEMENT THIS: (just a placeholder)
PieceEnum Board::getPiece(int x, int y)
{
    return PieceEnum::Rook;  
}