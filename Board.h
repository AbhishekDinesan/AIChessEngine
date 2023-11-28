

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "square.h"

class Board
{
    std::vector<Square> squares;

public:
    Board();
    ~Board();

    void addPiece();
    void removePiece();
    bool isOccupied();
    bool isCovered();
    // Piece getPiece();
};

#endif
