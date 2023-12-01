#include <stdexcept>
#include "Board.h"
#include "NonePiece.h"
#include "square.h"
#include "stdexcept"
#include "textdisplay.h"
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include "RookPiece.h"
#include "BishopPiece.h"
#include "KnightPiece.h"
#include "QueenPiece.h"
#include "KingPiece.h"
#include <stdio.h>
using namespace std;

// constructor for Board
Board::Board() /*: squares(8, std::vector<Square>(8)*)*/
{
    
    TextDisplay *newTextDisplay = new TextDisplay;
    td = newTextDisplay;

    squares.resize(8);
    for (int row = 0; row < 8; ++row) {
        squares[row].resize(8);
        for (int col = 0; col < 8; ++col) {
            squares[row][col].setCoords(col, row);
            squares[row][col].attach(td);
        }
    }

    Rook *blackLRook = new Rook(false, true, true, 0, 0);
    Rook *blackRiRook = new Rook(false, true, true, 7, 0);
    squares[0][0].setPiece(blackLRook);
    squares[7][0].setPiece(blackRiRook);

    Knight *blackLKnight = new Knight(false, true, 1, 0);
    Knight *blackRKnight = new Knight(false, true, 6, 0);
    squares[1][0].setPiece(blackLKnight);
    squares[6][0].setPiece(blackRKnight);

    Bishop *blackLBishop = new Bishop(false, true, 2, 0);
    Bishop *blackRBishop = new Bishop(false, true, 5, 0);
    squares[2][0].setPiece(blackLBishop);
    squares[5][0].setPiece(blackRBishop);

    Queen *blackQueen = new Queen(false, true, 4, 0);
    squares[4][0].setPiece(blackQueen);

    King *blackKing = new King(false, true, false, false,  5, 0);
    squares[3][0].setPiece(blackKing);

    // PAWNS
    for (int col = 0; col < 8; ++col) {
        Pawn *blackPawn = new Pawn(false, true, false, col, 1);
        squares[col][1].setPiece(blackPawn); // SWapped ROWS/COLS
     }
    
    // EMPTY SPACES
    for (int row = 2; row < 6; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            None *emptypiece = new None(col, row);
            squares[col][row].setPiece(emptypiece);
        }
    }
    

    for (int col = 0; col < 8; ++col) {
        Pawn *whitePawn = new Pawn(true, true, false, col, 6);
        squares[col][6].setPiece(whitePawn);
    }

    Rook *whiteLRook = new Rook(true, true, true, 0, 7);
    Rook *whiteRiRook = new Rook(true, true, true, 7, 7);
    squares[0][7].setPiece(whiteLRook);
    squares[7][7].setPiece(whiteRiRook);

    Knight *whiteLKnight = new Knight(true, true, 1, 7);
    Knight *whiteRKnight = new Knight(true, true, 6, 7);
    squares[1][7].setPiece(whiteLKnight);
    squares[6][7].setPiece(whiteRKnight);

    Bishop *whiteLBishop = new Bishop(true, true, 2, 7);
    Bishop *whiteRBishop = new Bishop(true, true, 5, 7);
    squares[2][7].setPiece(whiteLBishop);
    squares[5][7].setPiece(whiteRBishop);

    Queen *whiteQueen = new Queen(true, true, 3, 7);
    squares[3][7].setPiece(whiteQueen);

    King *whiteKing = new King(true, true, false, false, 4, 7);
    squares[4][7].setPiece(whiteKing);

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

std::ostream &operator<<(std::ostream &out, const Board &b)
{
    out << *(b.td);
    return out;
}

// implementation for this needs to wait until we define pieces:
// Piece Board::getPiece()
// {
//     // Implementation to get a piece from the board
//     // You may need to define the Piece class and return an instance of it
// }