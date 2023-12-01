

#ifndef __GAME_H__
#define __GAME_H__

#include "Board.h"
#include "AbstractPlayer.h"
#include "Player.h"
#include "textdisplay.h"
using namespace std;

// class Board; forward declerations
// class Player;

using namespace std;  

class Game
{
    Player *PlayerOne;
    Player *PlayerTwo;
    //  Player currentPlayer;
    int moveCount;
    // Vector pastMoves;
    unique_ptr<Board> board; 

public:
    Game();
    ~Game();

    void init();
    bool ValidBoard();
    bool endGame();
    
    
    void printBoard();
    std::unique_ptr<Board>& getBoard(); 
    void addPiece(char piece, int x, int y);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
 
};

#endif
