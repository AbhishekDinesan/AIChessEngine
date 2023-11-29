#include <stdexcept>
#include "Board.h"
#include "NonePiece.h"
#include "square.h"
#include "stdexcept"
#include "textdisplay.h"

// constructor for Board
Board::Board() : squares(8, std::vector<Square>(8))
{
    TextDisplay *newTextDisplay = new TextDisplay();
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            None *emptypiece = new None();
            squares[x][y].setPiece(emptypiece);
        }
    }
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
    None *nonePiece = new None();
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

// implementation for this needs to wait until we define pieces:
// Piece Board::getPiece()
// {
//     // Implementation to get a piece from the board
//     // You may need to define the Piece class and return an instance of it
// }