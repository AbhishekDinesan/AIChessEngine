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
    struct coords {int x, y;};
    coords From;
    coords To;
    Piece *captured; 
    bool didcapture; 

public:
    Move(Board *board, Piece *piece, coords From, coords To); 
    ~Move();
    Piece* CapturedPiece();
    bool isCheck();
    void UpdateBoard();
    // possibleMoves(); IDK WHAT TYPE THIS SHOULD BE SO I COMMENTED IT OUT SO IT DOESN'T COMPLAIN
    bool willCheck();
    bool executeMove(Game *g, int x, int y, Piece *p); 

};

#endif