
#include "Board.h"
#include "square.h" // Include the header for the Square class
Board::Board() {
}


Board::~Board() {
}

void Board::addPiece() {
}


void Board::removePiece() {
    // Implementation to remove a piece from the vector
    if (!squares.empty())
    {
        squares.pop_back(); // Remove the last element from the vector
    }
}

bool Board::isOccupied() {
}

bool Board::isCovered() {
}

// Piece Board::getPiece()
// {
//     // Implementation to get a piece from the board
//     // You may need to define the Piece class and return an instance of it
// }