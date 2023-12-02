#ifndef __MOVE_H__
#define __MOVE_H__

#include <stdlib.h> 
#include <vector>

class Piece; 
class Board; 

//add a square class

class Game; 

class Move
{
    Board *board;
    //Piece *piece;
    int fromX, fromY, toX, toY;
    Piece *captured; 
    bool didcapture; 

 public:
    Move(Board *board, int fromX, int fromY, int toX, int toY); 
    ~Move();
    Piece* CapturedPiece();
    bool isCheck();
    void UpdateBoard();
    std::vector<Move> possibleMoves(Piece *p);   
    bool willCheck();
    bool isValidMove(); 
};

#endif