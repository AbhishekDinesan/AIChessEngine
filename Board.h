

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "square.h"

class Board
{
    //2D Vector of Squares to represent the board. 
    std::vector<std::vector<Square>> squares; 

public:
    Board();
    ~Board();

    void addPiece(int x, int y, Piece &p);
    void removePiece(int x, int y);
    bool isOccupied(int x, int y);
    bool isCovered(int x, int y);
    // Piece getPiece();


    bool isCheck();
    bool isCheckMate(); 
    void undoMove(); 

};

#endif
