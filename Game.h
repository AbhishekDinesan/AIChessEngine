

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
    Board* board;
    AbstractPlayer *whitePlayer;
    AbstractPlayer *blackPlayer;
    bool whiteToMove;
    int moveCount;
    bool gameOver;
    // Vector pastMoves;

public:
    Game(AbstractPlayer* white, AbstractPlayer* black, bool whiteToMove, bool customProvided, Board *theCustomBoard);
    ~Game();

    void init();
    bool ValidBoard();
    bool endGame();
    void movePiece(int fromX, int fromY, int toX, int toY);
    void printBoard();
    AbstractPlayer* getCurrPlayer();
    bool getCurrTurn();
    bool getGameOver();
    bool setGameOver(bool over);
    void addPiece(int x, int y, char piece);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
