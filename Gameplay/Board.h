

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "square.h"
#include <iostream>
#include "textdisplay.h"

class Board
{
    // 2D Vector of Squares to represent the board.
    TextDisplay *td;
    // GraphicsDisplay *gd;

public:
    std::vector<std::vector<Square>> squares; // made this public temporary
    bool isWhiteTurn;
    Board(bool emptyBoard, bool temp);
    ~Board();

    void addPiece(int x, int y, char c);
    void removePiece(int x, int y);
    bool isOccupied(int x, int y);
    bool isCovered(int x, int y);

    // PieceEnum getPiece(int x, int y);
    Piece *getPiecePtr(int x, int y);

    bool isValid();
    bool isCheck(bool KingColor);
    bool isCheckMate(bool KingColor);
    bool isStaleMate(bool KingColor);
    void movePiece(int fromX, int fromY, int toX, int toY);
    void setTurn(bool isWhite);
    void undoMove();
    void printBoard();
    friend class Move;
    friend std::ostream &operator<<(std::ostream &out, const Board &b);

    std::vector<int> findKing(bool isWhite);
};

#endif