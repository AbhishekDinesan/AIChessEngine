

#ifndef __GAME_H__
#define __GAME_H__

#include "Board.h"
#include "AbstractPlayer.h"
#include "Player.h"
#include "textdisplay.h"
using namespace std;

// class Board; forward declerations
// class Player;

class Game
{
    unique_ptr<Board> board;
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
    void addPiece(char piece, int x, int y);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
