

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
    Player *whitePlayer;
    Player *blackPlayer;
    bool whiteToMove;
    int moveCount;
    // Vector pastMoves;

public:
    Game(bool whiteToMove, bool customProvided, Board* theCustomBoard);
    ~Game();

    void init();
    bool ValidBoard();
    bool endGame();
    void movePiece(int fromX, int fromY, int toX, int toY);
    void printBoard();
    void addPiece(int x, int y, char piece);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
