

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "square.h"
#include <iostream>
#include "textdisplay.h"

class Board
{
    // 2D Vector of Squares to represent the board.

public:
    std::vector<std::vector<Square>> squares; // made this public temporary
    Board(bool emptyBoard);
    ~Board();

    TextDisplay *td;
    void addPiece(int x, int y, char c);
    void removePiece(int x, int y);
    bool isOccupied(int x, int y);
    bool isCovered(int x, int y);

    // PieceEnum getPiece(int x, int y);
    Piece *getPiecePtr(int x, int y);

    bool isValid();
    bool isCheck();
    bool isCheckMate();
    void movePiece(int fromX, int fromY, int toX, int toY);
    void undoMove();
    friend class Move;
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif