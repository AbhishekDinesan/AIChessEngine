/*

#ifndef __GAME_H__
#define __GAME_H__

#include Vector;

class Game
{
    Board *board;
    Player PlayerOne;
    Player PlayerTwo;
    Player currentPlayer;
    int moveCount;
    Vector pastMoves;

public:
    Game();
    ~Game();

    void init();
    bool ValidBoard();
    bool endGame();
    void movePiece();

};

#endif

*/