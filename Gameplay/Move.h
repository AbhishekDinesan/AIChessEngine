#ifndef __MOVE_H__
#define __MOVE_H__

#include <stdlib.h>
#include <vector>

class Piece;
class Board;

// add a square class

class Game;

class Move
{
    Board *board;
    // Piece *piece;

    Piece *captured;
    bool didcapture;

public:
    int fromX, fromY, toX, toY;

    Move(Board *board, int fromX, int fromY, int toX, int toY);
    ~Move();
    Piece *CapturedPiece();
    bool isCheck();
    void UpdateBoard();
    std::vector<Move> possibleMoves(Piece *p);
    bool willCapture();
    bool willCheck();
    bool isValidMove();
};

#endif