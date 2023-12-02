#ifndef __MOVE_H__
#define __MOVE_H__


class Piece; 
class Board; 

//add a square class

class Game; 

class Move
{
    Board *board;
    Piece *piece;
    int fromX, fromY, toX, toY;
    Piece *captured; 
    bool didcapture; 

 public:
    Move(Board *board, int fromX, int fromY, int toX, int toY); 
    ~Move();
    Piece* CapturedPiece();
    bool isCheck();
    void UpdateBoard();
    // possibleMoves(); IDK WHAT TYPE THIS SHOULD BE SO I COMMENTED IT OUT SO IT DOESN'T COMPLAIN
    bool willCheck();
    bool isValidMove(); 
};

#endif