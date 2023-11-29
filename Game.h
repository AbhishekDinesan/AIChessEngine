

#ifndef __GAME_H__
#define __GAME_H__

#include "Board.h"
#include "AbstractPlayer.h"
#include "Player.h"
#include "textdisplay.h"

// class Board; forward declerations
// class Player;

class Game
{
    Board *board;
    Player *PlayerOne;
    Player *PlayerTwo;
    //  Player currentPlayer;
    int moveCount;
    // Vector pastMoves;

public:
    Game();
    ~Game();

    void init();
    bool ValidBoard();
    bool endGame();
    void movePiece();
    void printBoard();
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
