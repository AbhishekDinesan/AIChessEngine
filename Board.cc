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
#include <vector> 

using namespace std;

// constructor for Board
Board::Board(bool emptyBoard, bool temp) /*: squares(8, std::vector<Square>(8)*)*/
{
    TextDisplay *newTextDisplay = new TextDisplay;
    td = newTextDisplay;

    if (!temp)
    {
        // Xwindow* w = new Xwindow();
        // gd = new GraphicsDisplay(*w);
    }
    squares.resize(8);
    for (int row = 0; row < 8; ++row)
    {
        squares[row].resize(8);
        for (int col = 0; col < 8; ++col)
        {
            delete squares[row][col].getOccupyingPc();
            squares[row][col].setCoords(col, row);
            squares[row][col].attach(td);
            // squares[row][col].attach(gd);
        }
    }

    if (emptyBoard && !temp)
    {
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                None *emptypiece = new None(col, row);
                squares[col][row].setPiece(emptypiece);
            }
        }
        return;
    }
    

    Rook *blackLRook = new Rook(false, true, 0, 0, true);
    Rook *blackRiRook = new Rook(false, true, 7,0, true); 
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

    King *blackKing = new King(false, true, 5, 0, false, false);
    squares[3][0].setPiece(blackKing);

    // PAWNS
    for (int col = 0; col < 8; ++col)
    {
        Pawn *blackPawn = new Pawn(false, true, true, col, 1);
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

    for (int col = 0; col < 8; ++col)
    {
        Pawn *whitePawn = new Pawn(true, true, true, col, 6);
        squares[col][6].setPiece(whitePawn);
    }

    Rook *whiteLRook = new Rook(true, true, 0, 7, true);
    Rook *whiteRiRook = new Rook(true, true, 7, 7, true);
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

    King *whiteKing = new King(true, true, 4, 7, false, false);
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

// this function deleted the "old piece" and replaces the piece at the new index with the one we are moving
// replaces the piece at the old position with a None piece.
void Board::movePiece(int fromX, int fromY, int toX, int toY)
{
    cout << "(2)" << endl;
    Piece *movedPiece = squares[fromX][fromY].getOccupyingPc();
    cout << "(3)" << endl;
    delete squares[toX][toY].getOccupyingPc();

    None *emptyPiece = new None(fromX, fromY);
    squares[fromX][fromY].setPiece(emptyPiece);
    movedPiece->setX(toX);
    movedPiece->setY(toY);
    squares[toX][toY].setPiece(movedPiece);
}

void Board::addPiece(int x, int y, char c)
{
    // make sure that coordinates are within bounds
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        throw std::out_of_range("Coordinates are out of the board's bounds.");
    }

    delete squares[x][y].getOccupyingPc();

    Piece *p;
    if (c == 'K')
    {
        p = new King(true, true, x, y, false, false);
    }
    else if (c == 'k')
    {
        p = new King(false, true, x, y, false, false);
    }
    else if (c == 'Q')
    {
        p = new Queen(true, true, x, y);
    }
    else if (c == 'q')
    {
        p = new Queen(false, true, x, y);
    }
    else if (c == 'R')
    {
        // Potential for adding castling rights (AS OF NOW NO CASTLING WITH ADDED PIECES)
        p = new Rook(true, true, x, y, false);
    }
    else if (c == 'r')
    {
        // Potential for adding castling rights (AS OF NOW NO CASTLING WITH ADDED PIECES)
        p = new Rook(false, true, x, y, false);
    }
    else if (c == 'N')
    {
        p = new Knight(true, true, x, y);
    }
    else if (c == 'n')
    {
        p = new Knight(false, true, x, y);
    }
    else if (c == 'B')
    {
        p = new Bishop(true, true, x, y);
    }
    else if (c == 'b')
    {
        p = new Bishop(false, true, x, y);
    }
    else if (c == 'P')
    {
        // POTENTIAL FOR ADDING FIRST MOVE RIGHTS AND ENPASSANT PROPERTIES (AS OF NOW NONE OF THAT)
        p = new Pawn(true, true, false, x, y);
    }
    else if (c == 'p')
    {
        // POTENTIAL FOR ADDING FIRST MOVE RIGHTS AND ENPASSANT PROPERTIES (AS OF NOW NONE OF THAT)
        p = new Pawn(false, true, false, x, y);
    }

    squares[x][y].setPiece(p);
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

Piece *Board::getPiecePtr(int x, int y)
{
    cout << "(6)" << endl;
    return squares[x][y].getOccupyingPc();
}

bool Board::isValid()
{

    int whiteKingCount = 0;
    int blackKingCount = 0;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {

            // PAWNS ON FIRST AND LAST ROW
            if (row == 0 || row == 7)
            {
                if (squares[row][col].getOccupyingPc()->pieceType() == PieceEnum::Pawn)
                {
                    cerr << "Invalid Board Setup: No pawns can be placed on ranks 1 or 8" << endl;
                    cerr << "The board has been reverted to the default configuration." << endl;
                    return false;
                }
            }

            if (squares[row][col].getOccupyingPc()->pieceType() == PieceEnum::King)
            {
                (squares[row][col].getOccupyingPc()->getColour()) ? ++whiteKingCount : ++blackKingCount;
            }
        }
    }

    //
    // Check to see if board is in a checked position
    //

    if (whiteKingCount != 1 || blackKingCount != 1)
    {
        cerr << "Invalid Board Setup: There must be exactly one king of each colour on the board" << endl;
        cerr << "The board has been reverted to the default configuration." << endl;
        return false;
    }
}

void Board::printBoard()
{
    cout << *this->td;
}

std::ostream &operator<<(std::ostream &out, const Board &b)
{
    out << *(b.td);
    return out;
}

//iterate over each piece on the board, find the king.
vector<int> Board::findKing(bool isWhite) {
    vector<int> coords = {0, 0};
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (squares[row][col].getOccupyingPc()->pieceType() == PieceEnum::King && 
                squares[row][col].getOccupyingPc()->getColour() == isWhite) {
                    coords[0] = squares[row][col].getOccupyingPc()->getX();
                    coords[1] = squares[row][col].getOccupyingPc()->getY();
                }
        }
    }
    return coords;
}

bool Board::isCheck(bool kingColor) {
    vector<int> coords = findKing(kingColor); 
    vector<Move> moves; 

    int kingX = coords[0];
    int kingY = coords[1];

    int moveX = 0; 
    int moveY = 0; 

    for(int row = 0; row < 8; row ++) {
        for(int col = 0; col < 8; col ++) {
            Move currmove = Move(this, row, col, row, col); 

            std::vector<Move> currmoves = currmove.possibleMoves(this->getPiecePtr(row, col));  

            for(Move move: currmoves) {
                moveX = move.toX; 
                moveY = move.toY; 

                if(moveX == kingX && moveY == kingY) {
                    cout << "KING IN CHECK" << endl; 
                    return true; 
                }
            }
        }
    }
    
    cout << "KING NOT IN CHECK" << endl; 
    return false; 
}

// PieceEnum Board::getPiece(int x, int y) {
//  squares[x][y].getOccupyingPc()->pieceType();
//}