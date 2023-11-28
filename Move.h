#ifndef __MOVE_H__
#define __MOVE_H__


class Piece; 
class Board; 

//add a square class

class Move
{
    Board *board;
    Piece *piece;
    struct coords {int x, y;};
    coords From;
    coords To;

public:
    Move();
    ~Move();
    Piece* CapturedPiece();
    bool isCheck();
    void UpdateBoard();
    // possibleMoves(); IDK WHAT TYPE THIS SHOULD BE SO I COMMENTED IT OUT SO IT DOESN'T COMPLAIN
    bool willCheck();

};

#endif